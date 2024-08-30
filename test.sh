#!/bin/sh
# Simple test harness infrastructure
# Copyright 2005 by Rob Landley
# The following environment varAiables enable optional behavior in "testc":
#    DEBUG - Show every command run by test script.
#    VERBOSE - "all"    continue after failed test
#              "fail"   show diff and stop at first failed test
#              "nopass" don't show successful tests
#              "quiet"  don't show diff -u for failures
#              "spam"   show passing test command lines
#
# "testc" takes three arguments:
#	$1) Description to display when running command
#	$2) Command line arguments to command
#	$3) Expected result (on stdout)
#

: "${SHOWPASS:=PASS}" "${SHOWFAIL:=FAIL}" "${SHOWSKIP:=SKIP}" "${TESTDIR:=$(mktemp -d)}"
[ "${TESTDIR#*tmp.}" != "${TESTDIR}" ] && trap "rm -rf $TESTDIR" 0
if tty -s <&1
then
  SHOWPASS="$(printf "\033[1;32m%s\033[0m" "$SHOWPASS")"
  SHOWFAIL="$(printf "\033[1;31m%s\033[0m" "$SHOWFAIL")"
  SHOWSKIP="$(printf "\033[1;33m%s\033[0m" "$SHOWSKIP")"
fi

verbose_has() {
  [ "${VERBOSE#*"$1"}" != "$VERBOSE" ]
}

do_pass() {
  verbose_has nopass || printf "%s\n" "$SHOWPASS: $NAME"
}

do_fail() {
  printf "%s\n" "$SHOWFAIL: $NAME"
  if [ -n "$CASE" ]
  then
    echo "Expected '$CASE'"
    echo "Got '$A'"
  fi
  ! verbose_has all && exit 1
}

# testing: "name" "args" "result"
testc() {
  [ -z "$1" ] && NAME="$2" || NAME="$1"
  [ "${NAME#"$CMDNAME "}" = "$NAME" ] && NAME="$CMDNAME $1"

  [ -n "$DEBUG" ] && set -x

  if [ -n "$SKIP" ]
  then
    verbose_has quiet || printf "%s\n" "$SHOWSKIP: $NAME"
    return 0
  fi

  echo -n "$3" > "$TESTDIR"/expected
  ${EVAL:-eval} "$PROG $2" > "$TESTDIR"/actual
  RETVAL=$?

  # Catch segfaults
  [ "$RETVAL" -ne "0" ] &&
    echo "exited with signal (or returned $RETVAL)" >> "$TESTDIR"/actual
  DIFF="$(diff --color=always -au${NOSPACE:+w} $TESTDIR/expected $TESTDIR/actual 2>&1)"
  [ -z "$DIFF" ] && do_pass || VERBOSE=all do_fail
  if ! verbose_has quiet && { [ -n "$DIFF" ] || verbose_has spam; }
  then
    printf "%s\n" "$EVAL $PROG $2"
    [ -n "$DIFF" ] && printf "%s\n" "$DIFF"
  fi

  [ -n "$DIFF" ] && ! verbose_has all && exit 1
  rm -f "$TESTDIR"/input "$TESTDIR/"expected "$TESTDIR"/actual


  return 0
}

LONGSTRING="$(printf -- "a%150s" potato)"

PROGRAM () {
	echo "PROGRAM: $1"
	if [ -n "$TEST_HOST" ]; then
		$CC $CFLAGS test/$1.c -o test/tprogs/$1
	else
		$CC $CFLAGS $INCFLAGS $NOSTDFLAGS -L lib/ test/$1.c -o test/tprogs/$1 -lc
	fi
	PROG=test/tprogs/$1
}

test_group () {
	PROGRAM $1
	testc "GROUP $1" "" "$(cat test/files/${1}-desired)\n"
}

PROGRAM puts

testc "puts" "\"Hello World\"" "Hello World\n"
testc "puts newlines" "\"Hello 
World\"" "Hello 
World\n"
testc "puts long" "\"$LONGSTRING\"" "$LONGSTRING\n"
testc "puts empty" "\"\"" "\n"

PROGRAM putchar

testc "crti exit" "|| echo \$?" "42\n"
testc "putchar" "ExampleText" "ExampleText"

PROGRAM atexit

testc "atexit" "" "UwUUwUUwU\nUwUUwUUwU\nUwUUwUUwU\n"

PROGRAM assert

testc "assert" "||echo Yippe" "Yippe\n"

PROGRAM assert_NDEBUG

testc "NDEBUG" "&&echo Yippe" "Yippe\n"

PROGRAM strlen

testc "strlen" "abcdef" "6\n"

PROGRAM crti

testc "crti argc" "a b c d e f" "7\n"

PROGRAM abs

testc "abs" "" "0\n1\n350\n1\n350\n0\n1\n350\n1\n350\n"

PROGRAM printf # Also a varargs test

testc "printf %d %s basic" "" "Hello World, 34, -21, UwU, 2147483647\n"
testc "printf %f" "1" "2.500000, 0.012340, 250.000000, -120.000000, 999999999999999.000000, 18446744073709551616.000000\n"
# On NULL glibc prints (nil), musl prints 0 with no 0x prefix
testc "printf %p" "1 2" "0x1, 0xffffffffffffffff, 0xdeadbeef\n"


test_group ctype

PROGRAM macros

testc "macros" "" "1, 0, 0, -1"

PROGRAM fwrite

testc "fwrite" "|xxd" \
"00000000: 0200 0000 0300 0000 0400 0000 0500 0000  ................
00000010: 0600 0000                                ....
"

PROGRAM mallocsmall

testc "mallocsmall" "" "aaaa\n"

PROGRAM malloclarge

testc "malloclarge" "" ""

PROGRAM callocmixed

testc "callocmixed" "" ""

# Rounding-Error Level Percision loss that can't be fixed in a elegant manner, Also glibc libc/libm split
if [ -z "$TEST_HOST" ]; then
PROGRAM math
testc "math" "" "$(cat test/files/math-desired)\n"
#PROGRAM math2
#testc "math2" "" ""
PROGRAM env
export UwU="32" NYAH=" 53"
testc "getenv" "" "32  53 (nul)\n"

fi

PROGRAM iofile

testc "iofile" "&& cat test/files/iofile-examp" "42"

PROGRAM errno

testc "errno" "2>&1 | grep -c Meow" "1\n"

PROGRAM nconv

testc "atoi" "" "340 -1\n"

PROGRAM sort

testc "qsort" "f g h b c a" "a b c f g h "

PROGRAM rand

testc "rand" "| sort | uniq -d" ""

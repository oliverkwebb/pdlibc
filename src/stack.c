void __stack_chk_fail(void)
{
	*(int*)0 = 0;
}

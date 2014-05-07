 
#include "stdafx.h" 
#include <string.h>
//游戏 功能函数
byte chessdata[11][19];
 HWND gameh;
 RECT r1;
 POINT p;//x,y
 const PCHAR gameCaption="QQ游戏 - 连连看角色版";
 int i,j,x1,x2,y1,y2;
 int count = 0;
 void findPoint();
 void updatdChess();
 int getcount();
void startGame()
{
	
// TODO: Add your control notification handler code here
	//获取游戏窗口句柄
	gameh=::FindWindow(NULL,gameCaption);
	::GetWindowRect(gameh,&r1); 
	//保存当前鼠标指针
	   //取得当前鼠标位置
	GetCursorPos(&p);
	//设置鼠标指针位置  取开局所在坐标:x=655;y=577 //lparam 0x0241028f
	SetCursorPos(655+r1.left,577+r1.top);
	//模拟鼠标的 单击（鼠标按下/鼠标抬起）
	//MOUSEEVENTF_LEFTDOWN Specifies that the left button is down. 
    //MOUSEEVENTF_LEFTUP 
	//鼠标在当前位置按下
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	//鼠标在当前位置抬起
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	//还原鼠标位置
	Sleep(200);//过一段时间 再执行后边的代码
    SetCursorPos(p.x,p.y);
	
/*	
	*/
}
//游戏
int play()
{
	updatdChess();
	count = getcount();
	while(count != 0)
	{	
		findPoint();
		updatdChess();
		count = getcount();
	//Sleep(200);
	}
	return 1;
}
//获取数据
void updatdChess() //更新棋盘数据至 chessdata
{
	// TODO: Add your control notification handler code here
		//获取窗口句柄
	HWND gameh=::FindWindow(NULL,gameCaption);
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh,&processid);
	//打开指定进程
	HANDLE processH=::OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,false,processid);
	//读指定进程 内存数据
    DWORD byread;
	LPCVOID pbase=(LPCVOID)0x00129FB4; //棋盘数据基址
	LPVOID  nbuffer=(LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH,pbase,nbuffer,11*19,&byread);
}
//获取有多少数据不为0
int getcount()
{
	int i = 0;
	for (int y=0;y<=10;y++)
	 {
		 for (int x=0;x<=18;x++) //读一行
		 {
			if(chessdata[y][x] != 0)
				i++;

		 }
	}
	return i;
}

//模拟鼠标点击某一个图标
void press(POINT p)
{
	int   x=22,y=187;
	HWND hwnd=::FindWindow(NULL,gameCaption);
	int lparam;
	lparam=((y+35*p.y)<<16)+x+31*p.x;//表示指定格
	::SendMessage(hwnd,WM_LBUTTONDOWN,0,lparam);//
	::SendMessage(hwnd,WM_LBUTTONUP,0,lparam);  // 
}
//判断两个在同行或者同列上的点是否没有障碍,没有返回1，否则返回0
int p2check(POINT p1,POINT p2)
{
	//若两个点是同一个点，返回1
	//if((p1.x == p2.x) && (p1.y == p2.y))
	//	return 1;
	int x1,x2,y1,y2;
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	if(x1 == x2)
	{
		if(y1 > y2)
		{
			y2++;
			while(chessdata[y2][x1] == 0 && y2 < y1)
				y2++;
			if(y1 == y2)
				return 1;
			else
				return 0;
		}
//		y1 = p1.y;
//		y2 = p2.y;
		if(y1 < y2)
		{
			y1 ++;
		while(chessdata[y1][x1] == 0 && y1 < y2)
				y1 ++;
			if(y1 == y2)
				return 1;
			else
				return 0;
		}
	}
//	x1 = p1.x;
//	y1 = p1.y;
//	x2 = p2.x;
//	y2 = p2.y;
	if(y1 == y2)
	{
		if(x1 > x2)
		{
			x2 ++;
			while(chessdata[y1][x2] == 0 && x2 < x1)
				x2 ++;
			if(x1 == x2)
				return 1;
			else
				return 0;
		}
		else
		{
//		x1 = p1.x;
//		y1 = p1.y;
//		x2 = p2.x;
//		y2 = p2.y;
		x1 ++;
		while(chessdata[y1][x1] == 0 && x1 < x2)
				x1 ++;
			if(x1 == x2)
				return 1;
			else
				return 0;
		}
	}
}
/*
int p2check(POINT p1,POINT p2)
{
	//若两个点是同一个点，返回1
	if((p1.x == p2.x) && (p1.y == p2.y))
		return 1;
	int x1,x2,y1,y2;
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	if(x1 == x2)
	{
		if(y1 > y2)
		{
			y2++;
			while(chessdata[y2][x1] == 0 && y2 < y1)
				y2++;
			if(y1 == y2)
				return 1;
			else
				return 0;
		}
		y1 = p1.y;
		y2 = p2.y;
		if(y1 < y2)
		{
			y1 ++;
		while(chessdata[y1][x1] == 0 && y1 < y2)
				y1 ++;
			if(y1 == y2)
				return 1;
			else
				return 0;
		}
	}
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	if(y1 == y2)
	{
		if(x1 > x2)
		{
			x2 ++;
			while(chessdata[y1][x2] == 0 && x2 < x1)
				x2 ++;
			if(x1 == x2)
				return 1;
			else
				return 0;
		}
		else
		{
		x1 = p1.x;
		y1 = p1.y;
		x2 = p2.x;
		y2 = p2.y;
		x1 ++;
		while(chessdata[y1][x1] == 0 && x1 < x2)
				x1 ++;
			if(x1 == x2)
				return 1;
			else
				return 0;
		}
	}
}
*/
/*
//都往左移,成功为1，失败为0
int left(POINT p1,POINT p2)
{
	//让p1始终是在右边
	POINT temp;
	POINT p3,p4;
	if(p2.y > p1.y)
	{
		temp = p1;
		p1 = p2;
		p2 = temp;
	}
	
	i = (p1.y>p2.y)?p1.y:p2.y;//取较大值
	j = (p1.y<p2.y)?p1.y:p2.y;//取较小值
	if(i == j)//在同一列
	{
		return p2check(p1,p2);
	}
	//不在同一列的情况
	//首先将大值移动到小值一列上，然后一列一列往回判断
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	y1 = y1 - 1;//从下一列开始
	while(chessdata[y1--][x1] == 0 && y1>y2)
		;
	if(y1 != y2)//在之前就停住了，说明有障碍
		return 0;
	else
	{
		p3.x = p1.x;
		p4.x = p2.x;
		p4.y = p2.y;
		p3.y = p2.y;
		if(p2check(p3,p4) == 1)
			return 1;
		y1 = y1-1;//后一一位
		//y2 = y2-1;
		if(y1 < 0)
			return 0;
		while(chessdata[y1][x1] == 0 && chessdata[y1][x2] == 0)
		{
			if(y1 < 0)
				return 0;
			p3.y = y1;
			p4.y = y1;
			if(p2check(p3,p4) == 1)
				return 1;
			y1 -- ;
		}
	}		
}
//都往上移,成功为1，失败为0
int up(POINT p1,POINT p2)
{
	//让p1始终是在上边
	POINT temp;
	POINT p3,p4;
	if(p1.x > p2.x)
	{
		temp = p1;
		p1 = p2;
		p2 = temp;
	}
	//int large,small,i,j,x1,x2,y1,y2;
	i = p1.y>p2.y?p1.y:p2.y;//取较大值
	j = p1.y<p2.y?p1.y:p2.y;//取较小值
	if(i == j)//在同一列
	{
		return p2check(p1,p2);
	}
	//不在同一列的情况
	//首先将大值移动到小值一列上，然后一列一列往回判断
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	x2 = x2 - 1;
	while(chessdata[y2][x2--] == 0 && x2>x1)
		;
	if(x1 != x2)//在之前就停住了，说明有障碍
		return 0;
	else
	{
		//处理与p1点在一行的那个点
		p3.y = p1.y;
		p4.y = p2.y;
		p4.x = p1.x;
		p3.x = p1.x;
		if(p2check(p3,p4) == 1)
			return 1;
		x1 = x1-1;//后一一位
		//y2 = y2-1;
		if(x1 < 0)
			return 0;
		while(chessdata[y1][x1] == 0 && chessdata[y2][x1] == 0)
		{
			if(x1 < 0)
				return 0;
			p3.x = x1;
			p4.x = x1;
			if(p2check(p3,p4) == 1)
				return 1;
			x1 --;
		}
	}		
}

//都往右移,成功为1，失败为0
int right(POINT p1,POINT p2)
{
	//让p1始终是在右边
	POINT temp;
	POINT p3,p4;
	if(p2.y > p1.y)
	{
		temp = p1;
		p1 = p2;
		p2 = temp;
	}
	//int large,small,i,j,x1,x2,y1,y2;
	i = p1.y>p2.y?p1.y:p2.y;//取较大值
	j = p1.y<p2.y?p1.y:p2.y;//取较小值
	if(i == j)//在同一列
	{
		return p2check(p1,p2);
	}
	//不在同一列的情况
	//首先将大值移动到小值一列上，然后一列一列往回判断
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	y2 = y2 + 1;
	while(chessdata[y2++][x2] == 0 && y1>y2)
		;
	if(y1 != y2)//在之前就停住了，说明有障碍
		return 0;
	else
	{
		p3.x = p2.x;
		//p4.x = p2.x;
		//p4.y = p2.y;
		p3.y = p1.y;
		if(p2check(p3,p1) == 1)
			return 1;
		y1 = y1+1;//后一一位
		//y2 = y2-1;
		if(y1 > 10)
			return 0;
		while(chessdata[y1][x1] == 0 && chessdata[y1][x2] == 0)
		{
			if(y1 > 10)
				return 0;
			p3.y = y1;
			p4.y = y1;
			p4.x = p1.x;
			if(p2check(p3,p4) == 1)
				return 1;
			y1 ++ ;
		}
	}		
}

//都往下移,成功为1，失败为0
int down(POINT p1,POINT p2)
{
	//让p1始终是在上边
	POINT temp;
	POINT p3,p4;
	if(p1.x > p2.x)
	{
		temp = p1;
		p1 = p2;
		p2 = temp;
	}
	//int large,small,i,j,x1,x2,y1,y2;
	i = p1.y>p2.y?p1.y:p2.y;//取较大值
	j = p1.y<p2.y?p1.y:p2.y;//取较小值
	if(i == j)//在同一列
	{
		return p2check(p1,p2);
	}
	//不在同一列的情况
	//首先将大值移动到小值一列上，然后一列一列往回判断
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	x1 = x1 + 1;
	while(chessdata[y1][x1++] == 0 && x2>x1)
		;
	if(x1 != x2)//在之前就停住了，说明有障碍
		return 0;
	else
	{
		//处理与p1点在一行的那个点
		p3.y = p1.y;
		p4.y = p2.y;
		p4.x = p2.x;
		p3.x = p2.x;
		if(p2check(p3,p4) == 1)
			return 1;
		x1 = x1 + 1;//后一一位
		//y2 = y2-1;
		if(x1 > 18)
			return 0;
		while(chessdata[y1][x1] == 0 && chessdata[y2][x1] == 0)
		{
			if(x1 > 18)
				return 0;
			p3.x = x1;
			p4.x = x1;
			if(p2check(p3,p4) == 1)
				return 1;
			x1 ++;
		}
	}		
}

//都往中间,成功为1，失败为0
int center(POINT p1,POINT p2)
{
	POINT p3,p4;
	//int large,small,i,j,x1,x2,y1,y2;
	if(p1.x <= p2.x && p1.y >= p2.y)
	{
		if(p1.x == p2.x || p1.y == p2.y)
			return p2check(p1,p2);
		p3.y = p2.y;
		p4.y = p1.y;
		x2 = p2.x;
		x1 = p1.x;
		x2 = x2 - 1;
		while(x2 >= x1)
		{
			p3.x = x2;
			p4.x = x2;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			x2 --;
		}
		p3.x = p2.x;
		p4.x = p1.x;
		y1 = p1.y;
		y2 = p2.y;
		y2 ++;
		while(y2 <= y1)
		{
			p3.y = y2;
			p4.y = y2;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			y2++;
		}
	}
	if(p1.x <= p2.x && p1.y <= p2.y)
	{
		if(p1.x == p2.x || p1.y == p2.y)
			return p2check(p1,p2);
		p3.x = p1.x;
		p4.x = p2.x;
		y1 = p1.y;
		y2 = p2.y;
		y1 ++;
		while(y1 <= y2)
		{
			p3.y = y1;
			p4.y = y1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			y1 ++;
		}
		p3.y = p1.y;
		p4.y = p2.y;
		x1 = p1.x;
		x2 = p2.x;
		x1 ++;
		while(x1 <= x2)
		{
			p3.x = x1;
			p4.x = x1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			x1 ++;
		}
	}
	if(p1.x >= p2.x && p1.y <= p2.y)
	{
		if(p1.x == p2.x || p1.y == p2.y)
			return p2check(p1,p2);
		p3.y = p1.y;
		p4.y = p2.y;
		x1 = p1.x;
		x2 = p2.x;
		x1 --;
		while(x1 >= x2)
		{
			p3.x = p4.x = x1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			x1 --;
		}
		p3.x = p1.x;
		p4.x = p2.x;
		y1 = p1.y;
		y2 = p2.y;
		y1 ++;
		while(y1 <= y2)
		{
			p3.y = p4.y = y1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			y1 ++;
		}
	}
	if(p1.x >= p2.x && p1.y >= p2.y)
	{
		if(p1.x == p2.x || p1.y == p2.y)
			return p2check(p1,p2);
		p3.y = p1.y;
		p4.y = p2.y;
		x1 = p1.x;
		x2 = p2.x;
		x1 --;
		while(x1 >= x2)
		{
			p3.x = p4.x = x1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			x1 --;
		}
		p3.x = p1.x;
		p4.x = p2.x;
		y1 = p1.y;
		y2 = p2.y;
		y1 --;
		while(y1 >= y2)
		{
			p3.y = p4.y = y1;
			if(p2check(p1,p4) == 1 && p2check(p3,p4) == 1 && p2check(p3,p2) == 1)
				return 1;
			y1 --;
		}

	}
	return 0;
		
}
*/




/*
//判断一列
int rowcheck(POINT p1,POINT p2)
{
	int t,t1_1,t1_2,t2_1,t2_2;
	y1 = p1.y;
	y2 = p2.y;
	x1 = p1.x;
	x2 = p2.x;
	//取得最大点
	for(t = x1+1; t < 11; t++)
		if(chessdata[y1][t] != 0)
		{
			t1_1 = t - 1;
			break;
		}
	if(t == 11)
		t1_1 = 10;
	//取得最小值
	for(t = x1-1;t >=0;t--)
		if(chessdata[y1][t] != 0)
		{
			t1_2 = t + 1;
			break;
		}
	if(t < 0)
		t1_2 = 0;
	//取得最大点
	for(t = x2+1; t < 11; t++)
		if(chessdata[y1][t] != 0)
		{
			t2_1 = t - 1;
			break;
		}
	if(t == 11)
		t2_1 = 10;
	//取得最小值
	for(t = x2-1;t >=0;t--)
		if(chessdata[y1][t] != 0)
		{
			t2_2 = t + 1;
			break;
		}
	if(t < 0)
		t2_2 = 0;
	//寻找共同的区间




}


//可否消除
bool check2p(POINT p1,POINT p2)
{
	if(up(p1,p2) == 1)
		return true;
	else if(down(p1,p2) == 1)
		return true;
	else if(left(p1,p2) == 1)
		return true;
	else if(right(p1,p2) == 1)
		return true;
	else if(center(p1,p2) == 1)
		return true;
	else
		return false;
}
*/
int check2p(POINT p1,POINT p2)
{
	POINT p3,p4;
	x1 = p1.x;
	x2 = p2.x;
	y1 = p1.y;
	y2 = p2.y;


	//在同一列或者同一行的时候
	if(x1 == x2 || y1 == y2)
	{
		if(p2check(p1,p2) == 1)
			 return 1;
		else
		{
			if(x1 == x2)
			{
					p3.y = p1.y;
					p4.y = p2.y;
					for(i = 0; i < 19; i ++)
					{
						
						
						if(chessdata[y2][i] == 0 && chessdata[y1][i] == 0)
						{
							p4.x = i;
							p3.x = i;
							if(p2check(p1,p3) == 1 && p2check(p4,p2) == 1 && p2check(p3,p4) == 1)
							return 1;
						}
						
					}
			}	
			if(y1 == y2)
			{
				p3.x = p1.x;
				p4.x = p2.x;
				for(i = 0; i < 11; i++)
				{
					
						
						if(chessdata[i][x1] == 0 && chessdata[i][x2] == 0)
						{
							p4.y = i;
							p3.y = i;
							if(p2check(p1,p3) == 1 && p2check(p4,p2) == 1 && p2check(p3,p4) == 1)
								return 1;
						}
						
				}
			}
		}//else
	}
		p3.y = p1.y;
		p4.y = p2.y;
					
	for(i = 0; i < 19; i ++)
	{
		if(i == x1)
		{
			if(chessdata[y2][i] == 0)
			{
				p4.x = i;
				if(p2check(p1,p4) == 1 && p2check(p4,p2) == 1)
					return 1;
			}
		}
		if(i == x2)
		{
			if(chessdata[y1][i] == 0)
			{
				p4.x = i;
				if(p2check(p1,p4) == 1 && p2check(p4,p2) == 1)
					return 1;
			}
		}
		else
		{
		p3.x = p4.x = i;
		if(chessdata[y1][i] == 0 && chessdata[y2][i] == 0)
		{
		if( (p2check(p1,p3) == 1) && (p2check(p3,p4) == 1) && (p2check(p4,p2) == 1))
			return 1;
		}
		}
	}

	p3.x = p1.x;
	p4.x = p2.x;
	for(i = 0;i < 11;i ++)
	{
		if(i == y2)
		{
		if(chessdata[i][x1] == 0)
		{
			p4.y = i;
			if(p2check(p1,p4) == 1 && p2check(p2,p4) == 1)
				return 1;
		}
		}
		if(i == y1)
		{
			if(chessdata[i][x2] == 0)
			{
				p4.y = i;
				if(p2check(p1,p3) == 1 && p2check(p2,p4) == 1)
				return 1;
			}
		}
		else
		{
		p3.y = p4.y = i;
		if(chessdata[i][x1] != 0 && chessdata[i][x2] != 0)
		{
		if((p2check(p1,p3) == 1) && (p2check(p3,p4) == 1) && (p2check(p4,p2) == 1))
			return 1;
		}
		}
	}
	
	return 0;
}



//点击两个点
void click2p(POINT p1,POINT p2)
{
	press(p1);
	press(p2);
}



//查找两个相同点
void findPoint()
{
	//首先 更新棋盘
	updatdChess() ;
	POINT p1,p2;
	int x1,x2,y1,y2;
	for (y1=0;y1<11;y1++)
		  for (x1=0;x1<19;x1++)
		  {   
			  if(chessdata[y1][x1] != 0)
			  {
			  for (y2=0;y2<11;y2++)
			  for (x2=0;x2<19;x2++)
				  if ((chessdata[y1][x1]==chessdata[y2][x2]) // 棋子1与棋子2 类型是否相同
					  &&(!((x1==x2)&&(y1==y2)))  //要求点1与点2 相等则假
					  )
				  {  
					  p1.x=x1;p1.y=y1;
					  p2.x=x2;p2.y=y2;

					  if ( check2p(p1,p2) == 1)//如果可消除 则返回真
					 {
						 //click2p 鼠标模拟 点击 p1，p2
						 click2p(p1,p2);
						 count = count - 2;
					 }
				  }
			  }//if
		  }
}


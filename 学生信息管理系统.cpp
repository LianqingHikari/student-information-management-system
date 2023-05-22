#include <iostream>
#include <windows.h>
#include <graphics.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <algorithm>

using namespace std;

class student {
public:
    string student_id="";
};

class student_info:virtual public student {
public:
    string name="";
    string school="";
    string major="";
    string class_name="";
};

class student_score :virtual public student {
public:
    int math=0;
    int english=0;
    int programming=0;
    int physics=0;
};

class student_all_info :public student_info, public student_score {

};

/*界面*/
void A_LogIn();//登录
void A1_ShowError();//显示密码或账号错误
void B1_StuFunSelect();//学生选择功能界面
void B2_AdFunSelect();//管理员选择功能界面
void C1_StuInfoSearch();//学生查询信息界面
void C2_StuScoreSearch();//学生查询成绩界面
void C3_AdInfoManage();//管理员管理信息界面
void C4_AdScoreManage();//管理员管理成绩界面

/*比较器*/
bool com_stu_score_id_up(student_score s1, student_score s2) {
	return s1.student_id < s2.student_id;
}
bool com_stu_score_id_down(student_score s1, student_score s2) {
	return s1.student_id > s2.student_id;
}
bool com_stu_score_math_up(student_score s1, student_score s2) {
	return s1.math < s2.math;
}
bool com_stu_score_math_down(student_score s1, student_score s2) {
	return s1.math > s2.math;
}
bool com_stu_score_english_up(student_score s1, student_score s2) {
	return s1.english < s2.english;
}
bool com_stu_score_english_down(student_score s1, student_score s2) {
	return s1.english > s2.english;
}
bool com_stu_score_programming_up(student_score s1, student_score s2) {
	return s1.programming < s2.programming;
}
bool com_stu_score_programming_down(student_score s1, student_score s2) {
	return s1.programming > s2.programming;
}
bool com_stu_score_physics_up(student_score s1, student_score s2) {
	return s1.physics < s2.physics;
}
bool com_stu_score_physics_down(student_score s1, student_score s2) {
	return s1.physics > s2.physics;
}

bool com_stu_info_id_up(student_info s1, student_info s2) {
	return s1.student_id < s2.student_id;
}
bool com_stu_info_id_down(student_info s1, student_info s2) {
	return s1.student_id > s2.student_id;
}
bool com_stu_info_name_up(student_info s1, student_info s2) {
	return s1.name < s2.name;
}
bool com_stu_info_name_down(student_info s1, student_info s2) {
	return s1.name > s2.name;
}
bool com_stu_info_school_up(student_info s1, student_info s2) {
	return s1.school < s2.school;
}
bool com_stu_info_school_down(student_info s1, student_info s2) {
	return s1.school > s2.school;
}
bool com_stu_info_major_up(student_info s1, student_info s2) {
	return s1.major < s2.major;
}
bool com_stu_info_major_down(student_info s1, student_info s2) {
	return s1.major > s2.major;
}
bool com_stu_info_class_name_up(student_info s1, student_info s2) {
	return s1.class_name < s2.class_name;
}
bool com_stu_info_class_name_down(student_info s1, student_info s2) {
	return s1.class_name > s2.class_name;
}

int main()
{
	A_LogIn();
    return 0;
}

void A_LogIn() {
begin:
    MOUSEMSG m;//定义鼠标变量 m

    /*初始化*/
	initgraph(350, 250); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	char account[20] = {};
	char password[15] = {};
	int rem_password = 0;//奇偶变量，表示记住密码框的选中状态
	int show_password = 0;//奇偶变量，表示显示密码框的选中状态
	int rem_password_tag = 0;//奇偶变量，表示是否已经记住密码了
	fstream f;

	/*判断是否记住密码*/
	f.open("rempassword.txt", ios::in);//打开记录“记住密码”状态的文件
	f >> rem_password_tag;
	if (rem_password_tag == 1) {//如果已经记住了密码
		setfillcolor(BLACK);
		fillrectangle(60, 158, 70, 168);//记住密码框选中
		rem_password = 1;//变量为1
		f >> account >> password;//输入账号和密码
		settextcolor(BLACK);
		outtextxy(100, 78, _T(account));//显示账号
		for (int i = 0; i < strlen(password); i++) {//显示密码
			outtextxy(100 + i * 8, 128, _T('*'));
		}
	}
	f.close();

	/*设置框和框中的信息*/
	setlinecolor(BLACK);
	rectangle(100,78,240,98);//账号框
	rectangle(100, 128, 240, 148);//密码框
	rectangle(60, 178, 290, 208);//登录框
	rectangle(250, 78, 290, 98);//账号输入框
	rectangle(250, 128, 290, 148);//密码输入框
	rectangle(60, 158, 70, 168);//记住密码选择框
	rectangle(130, 158, 140, 168);//显示密码选择框
	RECT r1 = { 60,178,290,208 };
	settextcolor(BLACK);
	drawtext(_T("登录"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//登录文本
	RECT r2 = { 250,78,290,98 };
	settextcolor(BLACK);
	drawtext(_T("输入"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//账号输入
	RECT r3 = { 250,128,290,148 };
	settextcolor(BLACK);
	drawtext(_T("输入"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//密码输入

	/*设置文本*/
	settextstyle(16, 0, _T("宋体"));//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextcolor(BLACK);
	outtextxy(60, 80, _T("账号"));
	outtextxy(60, 130, _T("密码"));
	settextstyle(12, 0, _T("宋体"));
	outtextxy(75, 157, _T("记住密码"));
	outtextxy(145, 157, _T("显示密码"));
	settextstyle(16, 0, _T("楷体"));
	outtextxy(73, 30, _T("欢迎进入学生信息管理系统！"));
	
	/*按钮设定*/
	while(1) {
		m = GetMouseMsg();
		if (m.x >= 60 && m.y >= 178 && m.x <= 290 && m.y <= 208) {//登录键
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				string temp_account(account);
				string temp_password(password);
				if (temp_account == "123" && temp_password == "123") {
					B1_StuFunSelect();
					goto begin;
				}
				else if (temp_account == "321" && temp_password == "321") {
					B2_AdFunSelect();
					goto begin;
				}
				else {
					A1_ShowError();
					goto begin;
				}
			}
		}
		else if (m.x >= 250 && m.y >= 78 && m.x <= 290 && m.y <= 98) {//账号输入
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(account, 20, "请输入你的账号");
				clearrectangle(101, 79, 239, 97);
				outtextxy(100, 78, _T(account));
				if(rem_password==1) {//重新输入账号，记住密码框置零
					clearrectangle(60, 158, 70, 168);
					rectangle(60, 158, 70, 168);
					rem_password = 0;
					f.open("rempassword.txt", ios::out);
					f << 0;
					f.close();
				}
			}
		}
		else if (m.x >= 250 && m.y >= 128 && m.x <= 290 && m.y <= 148) {//密码输入
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(password, 15, "请输入你的密码");
				clearrectangle(101, 129, 239, 147);
				if (show_password == 0) {
					for (int i = 0; i < strlen(password); i++) {
						outtextxy(100 + i * 8, 128, _T('*'));
					}
				}
				else {
					outtextxy(100, 128, _T(password));
				}
				if (rem_password == 1) {//重新输入账号，记住密码框置零
					clearrectangle(60, 158, 70, 168);
					rectangle(60, 158, 70, 168);
					rem_password = 0;
					f.open("rempassword.txt", ios::out);
					f << 0;
					f.close();
				}
			}
		}
		else if (m.x >= 60 && m.y >= 158 && m.x <= 70 && m.y <= 168) {//记住密码
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				setfillcolor(BLACK);
				if (rem_password == 0) {
					fillrectangle(60, 158, 70, 168);
					rem_password = 1;
					if (account[0] != '\0' && password[0] != '\0') {
						f.open("rempassword.txt", ios::out);
						f << 1 << endl << account << endl << password << endl;
						f.close();
					}
				}
				else {
					clearrectangle(60, 158, 70, 168);
					rectangle(60, 158, 70, 168);
					rem_password = 0;
					f.open("rempassword.txt", ios::out);
					f << 0;
					f.close();
				}
			}
		}
		else if (m.x >= 130 && m.y >= 158 && m.x <= 140 && m.y <= 168) {//显示密码
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				setfillcolor(BLACK);
				if (show_password == 0) {
					fillrectangle(130, 158, 140, 168);
					show_password = 1;
					clearrectangle(101, 129, 239, 147);
					outtextxy(100, 128, _T(password));//显示密码
				}
				else {
					clearrectangle(130, 158, 140, 168);
					rectangle(130, 158, 140, 168);
					show_password = 0;

					clearrectangle(101, 129, 239, 147);
					for (int i = 0; i < strlen(password); i++) {//隐藏密码
						outtextxy(100 + i * 8, 128, _T('*'));
					}
				}
			}
		}
	}
	return;
}

void A1_ShowError() {
	settextstyle(12, 0, _T("宋体"));
	settextcolor(RED);
	outtextxy(200, 157, _T("账号或密码错误！"));
	settextcolor(BLACK);
	Sleep(300);
	clearrectangle(200, 157, 300, 170);
}

void B1_StuFunSelect() {
begin:
	MOUSEMSG m;//定义鼠标变量 m

	/*菜单*/
	initgraph(350, 250); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);

	rectangle(90, 78, 250, 118);//查询信息框
	rectangle(90, 148, 250, 188);//查询成绩框
	rectangle(290, 0, 340, 30);//返回框
	
	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r1 = { 90, 78, 250, 118 };
	drawtext(_T("查询信息"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//查询信息
	RECT r2 = { 90, 148, 250, 188 };
	drawtext(_T("查询成绩"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//查询成绩
	RECT r3 = { 290,0,340,30 };
	drawtext(_T("返回"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回

	
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(16, 0, _T("楷体"));
	outtextxy(95, 15, _T("许琪乐同学欢迎您！"));
	outtextxy(85, 40, _T("请选择您要执行的操作："));

	/*按钮设定*/
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 290 && m.y >= 0 && m.x <= 340 && m.y <= 30) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 90 && m.y >= 78 && m.x <= 250 && m.y <= 118) {//查询信息
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				C1_StuInfoSearch();//学生查询信息界面
				goto begin;
			}
		}
		else if (m.x >= 90 && m.y >= 148 && m.x <= 250 && m.y <= 188) {//查询成绩
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				C2_StuScoreSearch();//学生查询成绩界面
				goto begin;
			}
		}
	}
	return;
}

void B2_AdFunSelect() {
begin:
	MOUSEMSG m;//定义鼠标变量 m

	/*菜单*/
	initgraph(350, 300); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);

	rectangle(90, 78, 250, 118);//查询信息框
	rectangle(90, 148, 250, 188);//查询成绩框
	rectangle(90, 218, 250, 258);//打印所有信息框
	rectangle(290, 0, 340, 30);//返回框
	vector<student_all_info> stu_info_vec;

	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r1 = { 90, 78, 250, 118 };
	drawtext(_T("管理信息"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//登录文本
	RECT r2 = { 90, 148, 250, 188 };
	drawtext(_T("管理成绩"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//账号输入
	RECT r3 = { 290,0,340,30 };
	drawtext(_T("返回"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回
	RECT r4 = { 90, 218, 250, 258 };
	drawtext(_T("打印所有信息"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//打印所有信息


	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(16, 0, _T("楷体"));
	outtextxy(95, 15, _T("许琪乐管理员欢迎您！"));
	outtextxy(85, 40, _T("请选择您要执行的操作："));

	/*按钮设定*/
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 290 && m.y >= 0 && m.x <= 340 && m.y <= 30) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 90 && m.y >= 78 && m.x <= 250 && m.y <= 118) {//管理信息
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				C3_AdInfoManage();//管理员管理信息界面
				goto begin;
			}
		}
		else if (m.x >= 90 && m.y >= 148 && m.x <= 250 && m.y <= 188) {//管理成绩
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				C4_AdScoreManage();//管理员管理成绩界面
				goto begin;
			}
		}
		else if (m.x >= 90 && m.y >= 218 && m.x <= 250 && m.y <= 248) {//打印所有成绩
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				fstream f;
				
				f.open("stuinfo.txt", ios::in);
				while (f.peek() != EOF) {//将文件中的所有信息都放到向量中
					student_all_info temp_info;
					f >> temp_info.student_id >> temp_info.name >> temp_info.school >> temp_info.major >> temp_info.class_name;
					stu_info_vec.push_back(temp_info);
				}
				f.close();

				f.open("stuscore.txt", ios::in);
				while (f.peek() != EOF) {//将文件中的所有信息都放到向量中
					int flag = 0;
					student_all_info temp_info;
					f >> temp_info.student_id >> temp_info.math >> temp_info.english >> temp_info.programming >> temp_info.physics;
					for (int i = 0; i < stu_info_vec.size(); i++) {
						if (temp_info.student_id == stu_info_vec[i].student_id) {
							stu_info_vec[i].math = temp_info.math;
							stu_info_vec[i].english = temp_info.english;
							stu_info_vec[i].programming = temp_info.programming;
							stu_info_vec[i].physics = temp_info.physics;
							flag = 1;
						}
					}
					if(flag==0)stu_info_vec.push_back(temp_info);
				}
				f.close();

				f.open("stuallinfo.csv", ios::out);
				f << "学号" << ',' << "姓名" << ',' << "学院" << ',' << "专业" << ',' << "班级" << ',' << "数学" << ',' << "英语" << ',' << "编程" << ',' << "物理" << endl;
				for (int i = 0; i < stu_info_vec.size(); i++) {
					f << stu_info_vec[i].student_id << ',' << stu_info_vec[i].name << ',' << stu_info_vec[i].school << ',' << stu_info_vec[i].major << ',' << stu_info_vec[i].class_name << ',' << stu_info_vec[i].math << ',' << stu_info_vec[i].english << ',' << stu_info_vec[i].programming << ',' << stu_info_vec[i].physics << endl;
				}
				f.close();
			}
		}
	}
	return;
}


void C1_StuInfoSearch() {
	MOUSEMSG m;//定义鼠标变量 m

	/*初始化*/
	initgraph(950, 400); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);
	char temp_student_id[25] = {};//用于存放输入的信息
	char temp_name[25] = {};
	char temp_school[40] = {};
	char temp_major[25] = {};
	char temp_class_name[30] = {};
	fstream f;//输入输出文件
	vector<student_info> stu_info_vec;//用于保存文件中的所有结果
	vector<student_info> stu_info_vec_view;//用于保存文件中的部分结果，即视图

	rectangle(15, 30, 935, 380);//显示信息框
	rectangle(885, 0, 935, 25);//返回框
	rectangle(675, 0, 775, 25);//查询信息框

	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r0 = { 885, 0, 935, 25 };
	drawtext(_T("返回"), &r0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回
	RECT r7 = { 675, 0, 775, 25 };
	drawtext(_T("信息查询"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//查询信息

	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(18, 0, _T("楷体"));
	outtextxy(440, 0, _T("信息栏"));

	f.open("stuinfo.txt", ios::in | ios::out);
	/*输入文件*/
	while (f.peek() != EOF) {//将文件中的所有信息都放到向量中
		student_info temp_info;
		f >> temp_info.student_id >> temp_info.name >> temp_info.school >> temp_info.major >> temp_info.class_name;
		stu_info_vec.push_back(temp_info);
	}
	f.close();

	/*按钮设定*/
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 885 && m.y >= 0 && m.x <= 935 && m.y <= 25) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 675 && m.y >= 0 && m.x <= 775 && m.y <= 25) {//学号查询
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(16, 31, 934, 379);
				int M = 0;
				string str_name;//用于存放查询到的临时信息
				string str_school;
				string str_major;
				string str_class_name;
				string str_student_id;
				char ser_temp_student_id[25] = {};//用于查询到的临时信息
				char ser_temp_name[25] = {};
				char ser_temp_school[40] = {};
				char ser_temp_major[25] = {};
				char ser_temp_class_name[30] = {};
				vector<student_info>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end(); i++) {
					if (i->student_id == "201930640018") {
						str_name = i->name;
						str_school = i->school;
						str_major = i->major;
						str_class_name = i->class_name;
						M = 1;
						break;
					}
				}

				/*复制查询到的信息*/

				strcpy_s(ser_temp_name, str_name.c_str());
				strcpy_s(ser_temp_school, str_school.c_str());
				strcpy_s(ser_temp_major, str_major.c_str());
				strcpy_s(ser_temp_class_name, str_class_name.c_str());

				/*输出提示信息*/
				if (M == 1) {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(15, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					outtextxy(15, 50, _T("1"));
					outtextxy(55, 50, _T("201930640018"));
					outtextxy(160, 50, _T(ser_temp_name));
					outtextxy(327, 50, _T(ser_temp_school));
					outtextxy(575, 50, _T(ser_temp_major));
					outtextxy(745, 50, _T(ser_temp_class_name));
					outtextxy(15, 70, _T("查询到1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(15, 30, _T("查询到0行数据！"));
				}
			}
		}
	}
	return;
}

void C2_StuScoreSearch() {
	MOUSEMSG m;//定义鼠标变量 m

	/*初始化*/
	initgraph(400, 400); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);
	char temp_math[10] = {};
	char temp_english[10] = {};
	char temp_programming[10] = {};
	char temp_physics[10] = {};
	char temp_student_id[15] = {};
	fstream f;//输入输出文件
	vector<student_score> stu_score_vec;//用于保存文件中的所有结果
	vector<student_score> stu_score_vec_view;//用于保存文件中的部分结果，即视图

	rectangle(15, 30, 385, 380);//显示信息框
	rectangle(335, 0, 385, 25);//返回框
	rectangle(15, 0, 115, 25);//查询成绩框

	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r0 = { 335, 0, 385, 25 };
	drawtext(_T("返回"), &r0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回
	RECT r7 = { 15, 0, 115, 25 };
	drawtext(_T("查询成绩"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//查询成绩

	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(18, 0, _T("楷体"));
	outtextxy(170, 0, _T("信息栏"));

	f.open("stuscore.txt", ios::in | ios::out);
	/*输入文件*/
	while (f.peek() != EOF) {//将文件中的所有信息都放到向量中
		student_score temp_score;
		f >> temp_score.student_id >> temp_score.math >> temp_score.english >> temp_score.programming >> temp_score.physics;
		stu_score_vec.push_back(temp_score);
	}
	f.close();

	/*按钮设定*/
	while (1) {
		m = GetMouseMsg(); 
		if (m.x >= 335 && m.y >= 0 && m.x <= 385 && m.y <= 25) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 15 && m.y >= 0 && m.x <= 115 && m.y <= 25) {//查询成绩
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(16, 31, 384, 379);
				int M = 0;
				int str_student_id;
				int str_math;//用于存放查询到的临时信息
				int str_english;
				int str_programming;
				int str_physics;
				char ser_temp_student_id[15] = {};//用于查询到的临时信息
				char ser_temp_math[10] = {};
				char ser_temp_english[10] = {};
				char ser_temp_programming[10] = {};
				char ser_temp_physics[10] = {};
				vector<student_score>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end(); i++) {
					if (i->student_id == "201930640018") {
						str_math = i->math;
						str_english = i->english;
						str_programming = i->programming;
						str_physics = i->physics;
						M = 1;
						break;
					}
				}



				/*输出提示信息*/
				if (M == 1) {
					_itoa_s(str_math, ser_temp_math, 10);
					_itoa_s(str_english, ser_temp_english, 10);
					_itoa_s(str_programming, ser_temp_programming, 10);
					_itoa_s(str_physics, ser_temp_physics, 10);
					settextstyle(16, 0, _T("楷体"));
					outtextxy(15, 30, _T("序号 学号         数学 英语 编程 物理"));
					outtextxy(15, 50, _T("1"));
					outtextxy(55, 50, _T("201930640018"));
					outtextxy(160, 50, _T(ser_temp_math));
					outtextxy(201, 50, _T(ser_temp_english));
					outtextxy(242, 50, _T(ser_temp_programming));
					outtextxy(283, 50, _T(ser_temp_physics));
					outtextxy(15, 70, _T("查询到1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(15, 30, _T("查询到0行数据！"));
				}
			}
		}
	}
	return;
}

void C3_AdInfoManage() {
begin:
	MOUSEMSG m;//定义鼠标变量 m

	/*初始化*/
	initgraph(1150, 400); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);
	char temp_student_id[25] = {};//用于存放输入的信息
	char temp_name[25] = {};
	char temp_school[40] = {};
	char temp_major[25] = {};
	char temp_class_name[30] = {};
	fstream f;//输入输出文件
	vector<student_info> stu_info_vec;//用于保存文件中的所有结果
	vector<student_info> stu_info_vec_view;//用于保存文件中的部分结果，即视图

		/*比较器奇偶变量*/
	int stu_id = 0;
	int stu_name = 0;
	int stu_school = 0;
	int stu_major = 0;
	int stu_class_name = 0;


	/*文本框*/
	rectangle(285, 30, 1135, 380);//显示信息框
	rectangle(220, 5, 270, 35);//返回框
	rectangle(75, 45, 205,70);//姓名框
	rectangle(220, 45, 270, 70);//姓名输入
	rectangle(75, 95, 205, 120);//学院框
	rectangle(220, 95, 270, 120);//学院输入
	rectangle(75, 145, 205, 170);//专业框
	rectangle(220, 145, 270, 170);//专业输入
	rectangle(75, 195, 205, 220);//班级框
	rectangle(220, 195, 270, 220);//班级输入
	rectangle(75, 325, 205, 350);//学号框
	rectangle(30, 360, 205, 385);//学号输入
	rectangle(30, 245, 80, 270);//非学号删除框
	rectangle(100, 245, 200, 270);//非学号插入/修改框
	rectangle(220, 245, 270, 270);//非学号查询框
	rectangle(220, 325, 270, 350);//学号删除框
	rectangle(220, 360, 270, 385);//学号查询框
	rectangle(1035, 0, 1135, 25);//打印信息框
	rectangle(910, 0, 1010, 25);//保存修改框

	/*文本框输入*/
	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r0 = { 220, 5, 270, 35 };
	drawtext(_T("返回"), &r0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回
	RECT r1 = { 220, 45, 270, 70 };
	drawtext(_T("输入"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//姓名输入
	RECT r2 = { 220, 95, 270, 120 };
	drawtext(_T("输入"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学院输入
	RECT r3 = { 220, 145, 270, 170 };
	drawtext(_T("输入"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//专业输入
	RECT r4 = { 220, 195, 270, 220 };
	drawtext(_T("输入"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//班级输入
	RECT r5 = { 30, 360, 205, 385 };
	drawtext(_T("输入"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号输入
	RECT r6 = { 220, 325, 270, 350 };
	drawtext(_T("删除"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号删除
	RECT r7 = { 220, 360, 270, 385 };
	drawtext(_T("查询"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号查询
	RECT r8 = { 30, 245, 80, 270 };
	drawtext(_T("删除"), &r8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//非学号删除
	RECT r9 = { 100, 245, 200, 270 };
	drawtext(_T("插入/修改"), &r9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//插入/修改
	RECT r10 = { 220, 245, 270, 270 };
	drawtext(_T("查询"), &r10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//非学号查询
	RECT r11 = { 1035, 0, 1135, 25 };
	drawtext(_T("打印信息"), &r11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//打印信息
	RECT r12 = { 910, 0, 1010, 25 };
	drawtext(_T("保存修改"), &r12, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//保存修改

	/*文本*/
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(16, 0, _T("楷体"));
	outtextxy(100, 15, _T("非学号管理"));
	outtextxy(110, 300, _T("学号管理"));
	settextstyle(18, 0, _T("楷体"));
	outtextxy(680, 0, _T("信息栏"));
	
	
	settextstyle(16, 0, _T("宋体"));
	outtextxy(30, 50, _T("姓名"));
	outtextxy(30, 100, _T("学院"));
	outtextxy(30, 150, _T("专业"));
	outtextxy(30, 200, _T("班级"));
	outtextxy(30, 330, _T("学号"));

	f.open("stuinfo.txt", ios::in | ios::out);
	/*输入文件*/
	while (f.peek()!=EOF) {//将文件中的所有信息都放到向量中
		student_info temp_info;
		f >> temp_info.student_id >> temp_info.name >> temp_info.school >> temp_info.major >> temp_info.class_name;
		stu_info_vec.push_back(temp_info);
	}
	f.close();
	
anniu:
	/*按钮设定*/
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 220 && m.y >= 5 && m.x <= 270 && m.y <= 35) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 220 && m.y >= 45 && m.x <= 270 && m.y <= 70) {//输入姓名
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_name, 21, "请输入姓名");
				clearrectangle(76, 46, 204, 69);
				settextstyle(14, 0, _T("宋体"));
				outtextxy(75, 45, _T(temp_name));
			}
		}
		else if (m.x >= 220 && m.y >= 95 && m.x <= 270 && m.y <= 120) {//输入学院
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_school, 31, "请输入学院");
				clearrectangle(76, 96, 204, 119);
				settextstyle(13, 0, _T("宋体"));
				outtextxy(75, 95, _T(temp_school));
			}
		}
		else if (m.x >= 220 && m.y >= 145 && m.x <= 270 && m.y <= 170) {//输入专业
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_major, 21, "请输入专业");
				clearrectangle(76, 146, 204, 169);
				settextstyle(14, 0, _T("宋体"));
				outtextxy(75, 145, _T(temp_major));
			}
		}
		else if (m.x >= 220 && m.y >= 195 && m.x <= 270 && m.y <= 220) {//输入班级
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_class_name, 21, "请输入班级");
				clearrectangle(76, 196, 204, 219);
				settextstyle(14, 0, _T("宋体"));
				outtextxy(75, 195, _T(temp_class_name));
			}
		}
		else if (m.x >= 30 && m.y >= 360 && m.x <= 205 && m.y <= 385) {//输入学号
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_student_id, 13, "请输入学号（12位）");
				clearrectangle(76, 326, 204, 349);
				outtextxy(75, 325, _T(temp_student_id));
			}
		}
		else if (m.x >= 980 && m.y >= 0 && m.x <= 1080 && m.y <= 25) {//打印信息
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
					clearrectangle(286, 31, 1134, 379);
					fstream f;
					f.open("stuinfo.csv", ios::out);
					f << "学号" << ',' << "姓名" << ',' << "学校" << ',' << "专业" << ',' << "班级" << endl;
					for (int i = 0; i < stu_info_vec_view.size(); i++) {
						f << stu_info_vec_view[i].student_id << ',' << stu_info_vec_view[i].name << ',' << stu_info_vec_view[i].school << ',' << stu_info_vec_view[i].major << ',' << stu_info_vec_view[i].class_name << endl;
					}
					f.close();
					outtextxy(285, 30, _T("打印成功！"));
				}
			}
		}
		else if (m.x >= 100 && m.y >= 245 && m.x <= 200 && m.y <= 270) {//插入/修改
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				clearrectangle(286, 31, 1134, 379);
				int M = 0;
				string str_name(temp_name);
				string str_school(temp_school);
				string str_major(temp_major);
				string str_class_name(temp_class_name);
				string str_student_id(temp_student_id);
				vector<student_info>::iterator i;

				if (str_student_id.length() == 0) {
					outtextxy(285, 30, _T("学号不能为空！"));
					goto anniu;
				}

				/*如果存在相同信息，进行替换*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end(); i++) {
					if (i->student_id == str_student_id) {
						i->name = str_name;
						i->school = str_school;
						i->major = str_major;
						i->class_name = str_class_name;
						M = 1;
						break;
					}
				}
				
				/*输入学生信息*/
				if (M == 0) {
					student_info temp_stu;
					temp_stu.name = str_name;
					temp_stu.school = str_school;
					temp_stu.major = str_major;
					temp_stu.class_name = str_class_name;
					temp_stu.student_id = str_student_id;
					stu_info_vec.push_back(temp_stu);
				}

				/*输出提示信息*/
				settextstyle(16, 0, _T("楷体"));
				outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
				outtextxy(285, 50, _T("1"));
				outtextxy(325, 50, _T(temp_student_id));
				outtextxy(430, 50, _T(temp_name));
				outtextxy(597, 50, _T(temp_school));
				outtextxy(845, 50, _T(temp_major));
				outtextxy(1015, 50, _T(temp_class_name));
				if (M == 1) {
					outtextxy(285, 70, _T("该学生已存在！一行数据修改成功！"));
				}
				else {
					outtextxy(285, 70, _T("一行数据插入成功！"));
				}
			}
		}
		else if (m.x >= 220 && m.y >= 360 && m.x <= 270 && m.y <= 385) {//学号查询
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 1134, 379);
				int M = 0;
				string str_name;//用于存放查询到的临时信息
				string str_school;
				string str_major;
				string str_class_name;
				string str_student_id;
				char ser_temp_student_id[25] = {};//用于查询到的临时信息
				char ser_temp_name[25] = {};
				char ser_temp_school[40] = {};
				char ser_temp_major[25] = {};
				char ser_temp_class_name[30] = {};
				vector<student_info>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end(); i++) {
					if (i->student_id == temp_student_id) {
						str_name = i->name;
						str_school= i->school;
						str_major = i->major;
						str_class_name= i->class_name;
						M = 1;
						break;
					}
				}

				/*复制查询到的信息*/

				strcpy_s(ser_temp_name, str_name.c_str());
				strcpy_s(ser_temp_school, str_school.c_str());
				strcpy_s(ser_temp_major, str_major.c_str());
				strcpy_s(ser_temp_class_name, str_class_name.c_str());

				/*输出提示信息*/
				if (M == 1) {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					outtextxy(285, 50, _T("1"));
					outtextxy(325, 50, _T(temp_student_id));
					outtextxy(430, 50, _T(ser_temp_name));
					outtextxy(597, 50, _T(ser_temp_school));
					outtextxy(845, 50, _T(ser_temp_major));
					outtextxy(1015, 50, _T(ser_temp_class_name));
					outtextxy(285, 70, _T("查询到1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("查询到0行数据！"));
				}
			}
		}
		else if (m.x >= 220 && m.y >= 245 && m.x <= 270 && m.y <= 270) {//非学号查询
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 1134, 379);
				stu_info_vec_view.clear();
				int M = 0;//是否查询到了数据
				int count = 0;//查询成功的数目
				int MaxCon = 0;//条件数目
				string str_name;//用于存放查询到的临时信息
				string str_school;
				string str_major;
				string str_class_name;
				string str_student_id;
				char ser_temp_student_id[25] = {};//用于存放查询到的临时信息
				char ser_temp_name[25] = {};
				char ser_temp_school[40] = {};
				char ser_temp_major[25] = {};
				char ser_temp_class_name[30] = {};
				char ser_temp_num[1] = {};//序号数组
				vector<student_info>::iterator i;

				/*判断条件数量*/
				if (temp_name[0] != '\0')MaxCon++;
				if (temp_school[0] != '\0')MaxCon++;
				if (temp_major[0] != '\0')MaxCon++;
				if (temp_class_name[0] != '\0')MaxCon++;

				/*进行查询*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end(); i++) {
					int NowCon = 0;
					if (temp_name[0]!='\0' && i->name==temp_name) {
						NowCon++;
					}
					if (temp_school[0] != '\0' && i->school == temp_school) {
						NowCon++;
					}
					if (temp_major[0] != '\0' && i->major == temp_major) {
						NowCon++;
					}
					if (temp_class_name[0] != '\0' && i->class_name == temp_class_name) {
						NowCon++;
					}
					if (NowCon == MaxCon) {
						count++;
						student_info temp_info_view;
						temp_info_view.name = i->name;
						temp_info_view.school = i->school;
						temp_info_view.major = i->major;
						temp_info_view.class_name = i->class_name;
						temp_info_view.student_id = i->student_id;
						stu_info_vec_view.push_back(temp_info_view);
						M = 1;
					}
				}

				/*输出提示信息*/
				if (M == 1) {
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						ser_temp_num[0] = char(i + 49);
						outtextxy(286, 50+i*20, _T(ser_temp_num[0]));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i-1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(count + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("查询到0行数据！"));
				}
			}
		}
		else if (m.x >= 30 && m.y >= 245 && m.x <= 80 && m.y <= 270) {//非学号删除
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 1134, 379);
				int M = 0;//是否删除了数据
				int count = 0;//删除成功的数目
				int MaxCon = 0;//条件数目
				vector<student_info>::iterator i;

				/*判断条件数量*/
				if (temp_name[0] != '\0')MaxCon++;
				if (temp_school[0] != '\0')MaxCon++;
				if (temp_major[0] != '\0')MaxCon++;
				if (temp_class_name[0] != '\0')MaxCon++;

				/*进行查询*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end();) {
					int NowCon = 0;
					if (temp_name[0] != '\0' && i->name == temp_name) {
						NowCon++;
					}
					if (temp_school[0] != '\0' && i->school == temp_school) {
						NowCon++;
					}
					if (temp_major[0] != '\0' && i->major == temp_major) {
						NowCon++;
					}
					if (temp_class_name[0] != '\0' && i->class_name == temp_class_name) {
						NowCon++;
					}
					if (NowCon == MaxCon) {
						count++;
						i=stu_info_vec.erase(i);
						M = 1;
					}
					else {
						++i;
					}
				}

				/*输出提示信息*/
				if (M == 1) {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30 , _T("已删除"));
					outtextxy(335, 30 , _T(char(count + 48)));
					outtextxy(350, 30 , _T("行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除0行数据！"));
				}
			}
		}
		else if (m.x >= 220 && m.y >= 325 && m.x <= 270 && m.y <= 350) {//学号删除
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 1134, 379);
				int M = 0;
				vector<student_info>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_info_vec.begin(); i != stu_info_vec.end(); i++) {
					if (i->student_id == temp_student_id) {
						stu_info_vec.erase(i, i + 1);
						M = 1;
						break;
					}
				}

				/*输出提示信息*/
				if (M == 1) {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除0行数据！"));
				}
			}
		}
		else if (m.x >= 910 && m.y >= 0 && m.x <= 1010 && m.y <= 25) {//保存修改
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				f.open("stuinfo.txt", ios::out);
				int i = 0;
				for (i; i < stu_info_vec.size()-1; i++) {
					f << stu_info_vec[i].student_id << ' ' << stu_info_vec[i].name << ' ' << stu_info_vec[i].school << ' ' << stu_info_vec[i].major << ' ' << stu_info_vec[i].class_name << endl;
				}
				f << stu_info_vec[i].student_id << ' ' << stu_info_vec[i].name << ' ' << stu_info_vec[i].school << ' ' << stu_info_vec[i].major << ' ' << stu_info_vec[i].class_name;
				f.close();
				clearrectangle(286, 31, 1134, 379);
				settextstyle(16, 0, _T("楷体"));
				outtextxy(285, 30, _T("修改已保存！"));
			}
		}
		else if (m.x >= 325 && m.y >= 30 && m.x <= 357 && m.y <= 47) {//学号排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_id == 0) {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_id_up);
					stu_id = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_id_down);
					stu_id = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 428 && m.y >= 30 && m.x <= 462 && m.y <= 47) {//姓名排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_name == 0) {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_name_up);
					stu_name = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_name_down);
					stu_name = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 595 && m.y >= 30 && m.x <= 630 && m.y <= 47) {//学院排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_school == 0) {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_school_up);
					stu_school = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_id_down);
					stu_id = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 845 && m.y >= 30 && m.x <= 877 && m.y <= 47) {//专业排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_major == 0) {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_major_up);
					stu_major = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_major_down);
					stu_major = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 1013 && m.y >= 30 && m.x <= 1047 && m.y <= 47) {//班级排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_class_name == 0) {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_class_name_up);
					stu_class_name = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 1134, 379);
					sort(stu_info_vec_view.begin(), stu_info_vec_view.end(), com_stu_info_class_name_down);
					stu_class_name = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[25] = {};//用于查询到的临时信息
					char ser_temp_name[25] = {};
					char ser_temp_school[40] = {};
					char ser_temp_major[25] = {};
					char ser_temp_class_name[30] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         姓名                 学院                           专业                 班级                "));
					for (i = 0; i < stu_info_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));
						strcpy_s(ser_temp_student_id, stu_info_vec_view[i].student_id.c_str());
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));
						strcpy_s(ser_temp_name, stu_info_vec_view[i].name.c_str());
						outtextxy(430, 50 + i * 20, _T(ser_temp_name));
						strcpy_s(ser_temp_school, stu_info_vec_view[i].school.c_str());
						outtextxy(597, 50 + i * 20, _T(ser_temp_school));
						strcpy_s(ser_temp_major, stu_info_vec_view[i].major.c_str());
						outtextxy(845, 50 + i * 20, _T(ser_temp_major));
						strcpy_s(ser_temp_class_name, stu_info_vec_view[i].class_name.c_str());
						outtextxy(1015, 50 + i * 20, _T(ser_temp_class_name));
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_info_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
	}
	return;
}

void C4_AdScoreManage() {
begin:
	MOUSEMSG m;//定义鼠标变量 m

	/*初始化*/
	initgraph(600, 400); //定义画布大小，宽度，长度
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新
	setlinecolor(BLACK);
	char temp_math[10] = {};
	char temp_english[10] = {};
	char temp_programming[10] = {};
	char temp_physics[10] = {};
	char temp_student_id[15] = {};
	fstream f;//输入输出文件
	vector<student_score> stu_score_vec;//用于保存文件中的所有结果
	vector<student_score> stu_score_vec_view;//用于保存文件中的部分结果，即视图

		/*比较器奇偶变量*/
	int stu_id = 0;
	int stu_math = 0;
	int stu_english = 0;
	int stu_programming = 0;
	int stu_physics = 0;

	/*输入框*/
	rectangle(285, 30, 585, 380);//显示信息框
	rectangle(220, 5, 270, 35);//返回框
	rectangle(75, 45, 205, 70);//数学框
	rectangle(220, 45, 270, 70);//数学输入
	rectangle(75, 95, 205, 120);//英语框
	rectangle(220, 95, 270, 120);//英语输入
	rectangle(75, 145, 205, 170);//编程框
	rectangle(220, 145, 270, 170);//编程输入
	rectangle(75, 195, 205, 220);//物理框
	rectangle(220, 195, 270, 220);//物理输入
	rectangle(75, 325, 205, 350);//学号框
	rectangle(30, 360, 205, 385);//学号输入
	rectangle(30, 245, 80, 270);//非学号删除框
	rectangle(100, 245, 200, 270);//非学号插入/修改框
	rectangle(220, 245, 270, 270);//非学号查询框
	rectangle(220, 325, 270, 350);//学号删除框
	rectangle(220, 360, 270, 385);//学号查询框
	rectangle(485, 0, 585, 25);//打印信息框
	rectangle(285, 0, 385, 25);//保存修改框
	

	/*输入框文本*/
	settextcolor(BLACK);
	settextstyle(18, 0, _T("宋体"));//设置文字大小 格式 
	RECT r0 = { 220, 5, 270, 35 };
	drawtext(_T("返回"), &r0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回
	RECT r1 = { 220, 45, 270, 70 };
	drawtext(_T("输入"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//数学输入
	RECT r2 = { 220, 95, 270, 120 };
	drawtext(_T("输入"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//英语输入
	RECT r3 = { 220, 145, 270, 170 };
	drawtext(_T("输入"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//编程输入
	RECT r4 = { 220, 195, 270, 220 };
	drawtext(_T("输入"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//物理输入
	RECT r5 = { 30, 360, 205, 385 };
	drawtext(_T("输入"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号输入
	RECT r6 = { 220, 325, 270, 350 };
	drawtext(_T("删除"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号删除
	RECT r7 = { 220, 360, 270, 385 };
	drawtext(_T("查询"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//学号查询
	RECT r8 = { 30, 245, 80, 270 };
	drawtext(_T("删除"), &r8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//非学号查询
	RECT r9 = { 100, 245, 200, 270 };
	drawtext(_T("插入/修改"), &r9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//非学号查询
	RECT r10 = { 220, 245, 270, 270 };
	drawtext(_T("查询"), &r10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//非学号查询
	RECT r11 = { 485, 0, 585, 25 };
	drawtext(_T("打印信息"), &r11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//打印信息
	RECT r12 = { 285, 0, 385, 25 };
	drawtext(_T("保存修改"), &r12, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//保存修改

	/*文本信息*/
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextstyle(16, 0, _T("楷体"));
	outtextxy(100, 15, _T("非学号管理"));
	outtextxy(110, 300, _T("学号管理"));
	settextstyle(18, 0, _T("楷体"));
	outtextxy(400, 0, _T("信息栏"));
	settextstyle(16, 0, _T("楷体"));

	settextstyle(16, 0, _T("宋体"));
	outtextxy(30, 50, _T("数学"));
	outtextxy(30, 100, _T("英语"));
	outtextxy(30, 150, _T("编程"));
	outtextxy(30, 200, _T("物理"));
	outtextxy(30, 330, _T("学号"));

	f.open("stuscore.txt", ios::in | ios::out);
	/*输入文件*/
	while (f.peek() != EOF) {//将文件中的所有信息都放到向量中
		student_score temp_score;
		f >> temp_score.student_id >> temp_score.math >> temp_score.english >> temp_score.programming >> temp_score.physics;
		stu_score_vec.push_back(temp_score);
	}
	f.close();

anniu:
	/*按钮设定*/
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 220 && m.y >= 5 && m.x <= 270 && m.y <= 35) {//返回
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
		else if (m.x >= 220 && m.y >= 45 && m.x <= 270 && m.y <= 70) {//输入数学
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_math, 11, "请输入数学成绩（0~100）");
				clearrectangle(76, 46, 204, 69);
				outtextxy(75, 45, _T(temp_math));
			}
		}
		else if (m.x >= 220 && m.y >= 95 && m.x <= 270 && m.y <= 120) {//输入英语
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_english, 11, "请输入英语成绩（0~100）");
				clearrectangle(76, 96, 204, 119);
				outtextxy(75, 95, _T(temp_english));
			}
		}
		else if (m.x >= 220 && m.y >= 145 && m.x <= 270 && m.y <= 170) {//输入编程
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_programming, 11, "请输入编程成绩（0~100）");
				clearrectangle(76, 146, 204, 169);
				outtextxy(75, 145, _T(temp_programming));
			}
		}
		else if (m.x >= 220 && m.y >= 195 && m.x <= 270 && m.y <= 220) {//输入物理
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_physics, 11, "请输入物理成绩（0~100）");
				clearrectangle(76, 196, 204, 219);
				outtextxy(75, 195, _T(temp_physics));
			}
		}
		else if (m.x >= 30 && m.y >= 360 && m.x <= 205 && m.y <= 385) {//输入学号
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				InputBox(temp_student_id, 13, "请输入学号（12位）");
				clearrectangle(76, 326, 204, 349);
				outtextxy(75, 325, _T(temp_student_id));
			}
		}
		else if (m.x >= 485 && m.y >= 0 && m.x <= 585 && m.y <= 25) {//打印信息
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				clearrectangle(286, 31, 584, 379);
				fstream f;
				f.open("stuscore.csv", ios::out);
				f << "学号" << ',' << "数学" << ',' << "英语" << ',' << "编程" << ',' << "物理" << endl;
				for (int i = 0; i < stu_score_vec_view.size(); i++) {
					f << stu_score_vec_view[i].student_id << ',' << stu_score_vec_view[i].math << ',' << stu_score_vec_view[i].english << ',' << stu_score_vec_view[i].programming << ',' << stu_score_vec_view[i].physics << endl;
				}
				f.close();
				outtextxy(285, 30, _T("打印成功！"));
			}
		}
		else if (m.x >= 220 && m.y >= 360 && m.x <= 270 && m.y <= 385) {//学号查询
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 584, 379);
				int M = 0;
				int str_student_id;
				int str_math;//用于存放查询到的临时信息
				int str_english;
				int str_programming;
				int str_physics;
				char ser_temp_student_id[15] = {};//用于查询到的临时信息
				char ser_temp_math[10] = {};
				char ser_temp_english[10] = {};
				char ser_temp_programming[10] = {};
				char ser_temp_physics[10] = {};
				vector<student_score>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end(); i++) {
					if (i->student_id == temp_student_id) {
						str_math = i->math;
						str_english = i->english;
						str_programming = i->programming;
						str_physics = i->physics;
						M = 1;
						break;
					}
				}

				

				/*输出提示信息*/
				if (M == 1) {
					_itoa_s(str_math, ser_temp_math, 10);
					_itoa_s(str_english, ser_temp_english, 10);
					_itoa_s(str_programming, ser_temp_programming, 10);
					_itoa_s(str_physics, ser_temp_physics, 10);
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					outtextxy(285, 50, _T("1"));
					outtextxy(325, 50, _T(temp_student_id));
					outtextxy(430, 50, _T(ser_temp_math));
					outtextxy(471, 50, _T(ser_temp_english));
					outtextxy(512, 50, _T(ser_temp_programming));
					outtextxy(553, 50, _T(ser_temp_physics));
					outtextxy(285, 70, _T("查询到1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("查询到0行数据！"));
				}
			}
		}
		else if (m.x >= 220 && m.y >= 325 && m.x <= 270 && m.y <= 350) {//学号删除
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 584, 379);
				int M = 0;
				vector<student_score>::iterator i;

				/*如果存在相同信息，进行替换*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end(); i++) {
					if (i->student_id == temp_student_id) {
						stu_score_vec.erase(i, i + 1);
						M = 1;
						break;
					}
				}

				/*输出提示信息*/
				if (M == 1) {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除1行数据！"));
				}
				else {
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除0行数据！"));
				}
			}
		}
		else if (m.x >= 30 && m.y >=245 && m.x <= 80 && m.y <= 270) {//非学号删除
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 584, 379);
				stu_score_vec_view.clear();
				int M = 0;//是否查询到了数据
				int count = 0;//查询成功的数目
				int MaxCon = 0;//条件数目
				vector<student_score>::iterator i;
				/*用于存储输入的符号*/
				char temp_math_sign;//比较符
				int temp_math_up;//上界或者是某一个确定的范围界
				int temp_math_down;//下界，可能不用
				char temp_english_sign;//比较符
				int temp_english_up;
				int temp_english_down;
				char temp_programming_sign;//比较符
				int temp_programming_up;
				int temp_programming_down;
				char temp_physics_sign;//比较符
				int temp_physics_up;
				int temp_physics_down;

				/*判断条件数量*/
				if (temp_math[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_math);//设定串流
					ss >> temp_math_sign;//记录比较符
					if (temp_math_sign == '=' || temp_math_sign == '>' || temp_math_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_math_up;
					}
					else if (temp_math_sign == 'b') {//如果是b，输入上下界
						ss >> temp_math_up >> temp_math_down;
					}
				}
				if (temp_english[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_english);//设定串流
					ss >> temp_english_sign;//记录比较符
					if (temp_english_sign == '=' || temp_english_sign == '>' || temp_english_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_english_up;
					}
					else if (temp_english_sign == 'b') {//如果是b，输入上下界
						ss >> temp_english_up >> temp_english_down;
					}
				}
				if (temp_programming[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_programming);//设定串流
					ss >> temp_programming_sign;//记录比较符
					if (temp_programming_sign == '=' || temp_programming_sign == '>' || temp_programming_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_programming_up;
					}
					else if (temp_programming_sign == 'b') {//如果是b，输入上下界
						ss >> temp_programming_up >> temp_programming_down;
					}
				}
				if (temp_physics[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_physics);//设定串流
					ss >> temp_physics_sign;//记录比较符
					if (temp_physics_sign == '=' || temp_physics_sign == '>' || temp_physics_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_physics_up;
					}
					else if (temp_physics_sign == 'b') {//如果是b，输入上下界
						ss >> temp_physics_up >> temp_physics_down;
					}
				}

				/*进行删除*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end();) {
					int NowCon = 0;
					if (temp_math[0] != '\0') {
						if (temp_math_sign == '=' && i->math == temp_math_up)NowCon++;
						if (temp_math_sign == '<' && i->math < temp_math_up)NowCon++;
						if (temp_math_sign == '>' && i->math > temp_math_up)NowCon++;
						if (temp_math_sign == 'b' && i->math >= temp_math_up && i->math < temp_math_down)NowCon++;
					}
					if (temp_english[0] != '\0') {
						if (temp_english_sign == '=' && i->english == temp_english_up)NowCon++;
						if (temp_english_sign == '<' && i->english < temp_english_up)NowCon++;
						if (temp_english_sign == '>' && i->english > temp_english_up)NowCon++;
						if (temp_english_sign == 'b' && i->english >= temp_english_up && i->english < temp_english_down)NowCon++;
					}
					if (temp_programming[0] != '\0') {
						if (temp_programming_sign == '=' && i->programming == temp_programming_up)NowCon++;
						if (temp_programming_sign == '<' && i->programming < temp_programming_up)NowCon++;
						if (temp_programming_sign == '>' && i->programming > temp_programming_up)NowCon++;
						if (temp_programming_sign == 'b' && i->programming >= temp_programming_up && i->programming < temp_programming_down)NowCon++;
					}
					if (temp_physics[0] != '\0') {
						if (temp_physics_sign == '=' && i->physics == temp_physics_up)NowCon++;
						if (temp_physics_sign == '<' && i->physics < temp_physics_up)NowCon++;
						if (temp_physics_sign == '>' && i->physics > temp_physics_up)NowCon++;
						if (temp_physics_sign == 'b' && i->physics >= temp_physics_up && i->physics < temp_physics_down)NowCon++;
					}
					if (NowCon == MaxCon) {//所有的条件都满足的话
						count++;
						i=stu_score_vec.erase(i);
						M = 1;//删除标志位设定为1
					}
					else {
						++i;
					}
				}

				/*输出提示信息*/
				if (M == 1) {//找寻到信息
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除"));
					outtextxy(335, 30, _T(char(count + 48)));
					outtextxy(350, 30, _T("行数据！"));
				}
				else {//没有查询到信息
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("已删除0行数据！"));
				}
			}
		}
		else if (m.x >= 100 && m.y >= 245 && m.x <= 200 && m.y <= 270) {//插入/修改
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				clearrectangle(286, 31, 584, 379);
				int M = 0;
				vector<student_score>::iterator i;

				if (strlen(temp_student_id)==0) {
					outtextxy(285, 30, _T("学号不能为空！"));
					goto anniu;
				}

				/*如果存在相同信息，进行替换*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end(); i++) {
					if (i->student_id == temp_student_id) {
						i->math = atoi(temp_math);
						i->english = atoi(temp_english);
						i->programming = atoi(temp_programming);
						i->physics = atoi(temp_physics);
						M = 1;
						break;
					}
				}

				/*输入学生信息*/
				if (M == 0) {
					student_score temp_stu;
					temp_stu.math = atoi(temp_math);
					temp_stu.english = atoi(temp_english);
					temp_stu.programming = atoi(temp_programming);
					temp_stu.physics = atoi(temp_physics);
					temp_stu.student_id = temp_student_id;
					stu_score_vec.push_back(temp_stu);
				}

				/*输出提示信息*/
				settextstyle(16, 0, _T("楷体"));
				outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
				outtextxy(285, 50, _T("1"));
				outtextxy(325, 50, _T(temp_student_id));
				outtextxy(430, 50, _T(temp_math));
				outtextxy(471, 50, _T(temp_english));
				outtextxy(512, 50, _T(temp_programming));
				outtextxy(553, 50, _T(temp_physics));
				if (M == 1) {
					outtextxy(285, 70, _T("该学生已存在！一行数据修改成功！"));
				}
				else {
					outtextxy(285, 70, _T("一行数据插入成功！"));
				}
			}
		}
		else if (m.x >= 285 && m.y >= 0 && m.x <= 385 && m.y <= 25) {//保存修改
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				f.open("stuscore.txt", ios::out);
				int i = 0;
				for (i; i < stu_score_vec.size()-1; i++) {
					f << stu_score_vec[i].student_id << ' ' << stu_score_vec[i].math << ' ' << stu_score_vec[i].english << ' ' << stu_score_vec[i].programming << ' ' << stu_score_vec[i].physics << endl;
				}
				f << stu_score_vec[i].student_id << ' ' << stu_score_vec[i].math << ' ' << stu_score_vec[i].english << ' ' << stu_score_vec[i].programming << ' ' << stu_score_vec[i].physics;
				f.close();
				clearrectangle(286, 31, 584, 379);
				settextstyle(16, 0, _T("楷体"));
				outtextxy(285, 30, _T("修改已保存！"));
			}
		}
		else if (m.x >= 30 && m.y >= 245 && m.x <= 270 && m.y <= 270) {//非学号查询
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				/*初始化*/
				clearrectangle(286, 31, 584, 379);
				stu_score_vec_view.clear();
				int M = 0;//是否查询到了数据
				int count = 0;//查询成功的数目
				int MaxCon = 0;//条件数目
					/*用于查询到的临时信息*/
				char ser_temp_student_id[15] = {};
				char ser_temp_math[10] = {};
				char ser_temp_english[10] = {};
				char ser_temp_programming[10] = {};
				char ser_temp_physics[10] = {};
				vector<student_score>::iterator i;
					/*用于存储输入的符号*/
				char temp_math_sign;//比较符
				int temp_math_up;//上界或者是某一个确定的范围界
				int temp_math_down;//下界，可能不用
				char temp_english_sign;//比较符
				int temp_english_up;
				int temp_english_down;
				char temp_programming_sign;//比较符
				int temp_programming_up;
				int temp_programming_down;
				char temp_physics_sign;//比较符
				int temp_physics_up;
				int temp_physics_down;

				/*判断条件数量*/
				if (temp_math[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_math);//设定串流
					ss >> temp_math_sign;//记录比较符
					if (temp_math_sign == '='|| temp_math_sign == '>'|| temp_math_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_math_up;
					}
					else if (temp_math_sign == 'b') {//如果是b，输入上下界
						ss >> temp_math_up>> temp_math_down;
					}
				}
				if (temp_english[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_english);//设定串流
					ss >> temp_english_sign;//记录比较符
					if (temp_english_sign == '=' || temp_english_sign == '>' || temp_english_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_english_up;
					}
					else if (temp_english_sign == 'b') {//如果是b，输入上下界
						ss >> temp_english_up >> temp_english_down;
					}
				}
				if (temp_programming[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_programming);//设定串流
					ss >> temp_programming_sign;//记录比较符
					if (temp_programming_sign == '=' || temp_programming_sign == '>' || temp_programming_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_programming_up;
					}
					else if (temp_programming_sign == 'b') {//如果是b，输入上下界
						ss >> temp_programming_up >> temp_programming_down;
					}
				}
				if (temp_physics[0] != '\0') {
					MaxCon++;//如果非空，表示有一个条件
					istringstream ss(temp_physics);//设定串流
					ss >> temp_physics_sign;//记录比较符
					if (temp_physics_sign == '=' || temp_physics_sign == '>' || temp_physics_sign == '<') {//如果是这几个符号，只输入上界
						ss >> temp_physics_up;
					}
					else if (temp_physics_sign == 'b') {//如果是b，输入上下界
						ss >> temp_physics_up >> temp_physics_down;
					}
				}

				/*进行查询*/
				for (i = stu_score_vec.begin(); i != stu_score_vec.end(); i++) {
					int NowCon = 0;
					if (temp_math[0] != '\0') {
						if(temp_math_sign=='='&&i->math==temp_math_up)NowCon++;
						if (temp_math_sign == '<' && i->math < temp_math_up)NowCon++;
						if (temp_math_sign == '>' && i->math > temp_math_up)NowCon++;
						if (temp_math_sign == 'b' && i->math >=temp_math_up&& i->math < temp_math_down)NowCon++;
					}
					if (temp_english[0] != '\0') {
						if (temp_english_sign == '=' && i->english == temp_english_up)NowCon++;
						if (temp_english_sign == '<' && i->english < temp_english_up)NowCon++;
						if (temp_english_sign == '>' && i->english > temp_english_up)NowCon++;
						if (temp_english_sign == 'b' && i->english >= temp_english_up && i->english < temp_english_down)NowCon++;
					}
					if (temp_programming[0] != '\0') {
						if (temp_programming_sign == '=' && i->programming == temp_programming_up)NowCon++;
						if (temp_programming_sign == '<' && i->programming < temp_programming_up)NowCon++;
						if (temp_programming_sign == '>' && i->programming > temp_programming_up)NowCon++;
						if (temp_programming_sign == 'b' && i->programming >= temp_programming_up && i->programming < temp_programming_down)NowCon++;
					}
					if (temp_physics[0] != '\0') {
						if (temp_physics_sign == '=' && i->physics == temp_physics_up)NowCon++;
						if (temp_physics_sign == '<' && i->physics < temp_physics_up)NowCon++;
						if (temp_physics_sign == '>' && i->physics > temp_physics_up)NowCon++;
						if (temp_physics_sign == 'b' && i->physics >= temp_physics_up && i->physics < temp_physics_down)NowCon++;
					}
					if (NowCon == MaxCon) {//所有的条件都满足的话
						count++;
						student_score temp_score_view;//将对应的内容放入视图数组
						temp_score_view.math = i->math;
						temp_score_view.english = i->english;
						temp_score_view.programming = i->programming;
						temp_score_view.physics = i->physics;
						temp_score_view.student_id = i->student_id;
						stu_score_vec_view.push_back(temp_score_view);
						M = 1;//查询标志位设定为1
					}
				}

				/*输出提示信息*/
				if (M == 1) {//找寻到信息
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i+49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(),stu_score_vec_view[i].student_id.length()+1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(count + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {//没有查询到信息
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("查询到0行数据！"));
				}
			}
		}
		else if (m.x >= 325 && m.y >= 30 && m.x <= 355 && m.y <= 47) {//学号排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_id == 0) {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_id_up);
					stu_id = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_id_down);
					stu_id = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 428 && m.y >= 30 && m.x <= 460 && m.y <= 47) {//数学排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_math == 0) {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_math_up);
					stu_math = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_math_down);
					stu_math = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 469 && m.y >= 30 && m.x <= 501 && m.y <= 47) {//英语排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_english == 0) {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_english_up);
					stu_english = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_english_down);
					stu_english = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 509 && m.y >= 30 && m.x <= 542 && m.y <= 47) {//编程排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_programming == 0) {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_programming_up);
					stu_programming = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_programming_down);
					stu_programming = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
		else if (m.x >= 549 && m.y >= 30 && m.x <= 583 && m.y <= 47) {//物理排序
			if (m.uMsg == WM_LBUTTONUP) {//左键弹起时
				if (stu_physics==0) {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_physics_up);
					stu_physics = 1;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
				else {
					clearrectangle(286, 31, 584, 379);
					sort(stu_score_vec_view.begin(), stu_score_vec_view.end(), com_stu_score_physics_down);
					stu_physics = 0;

					/*定义临时存储单元*/
					char ser_temp_student_id[15] = {};
					char ser_temp_math[10] = {};
					char ser_temp_english[10] = {};
					char ser_temp_programming[10] = {};
					char ser_temp_physics[10] = {};

					/*输出信息*/
					int i;
					settextstyle(16, 0, _T("楷体"));
					outtextxy(285, 30, _T("序号 学号         数学 英语 编程 物理"));
					for (i = 0; i < stu_score_vec_view.size(); i++) {
						outtextxy(286, 50 + i * 20, _T(char(i + 49)));//输出序号
						strncpy_s(ser_temp_student_id, stu_score_vec_view[i].student_id.c_str(), stu_score_vec_view[i].student_id.length() + 1);
						outtextxy(325, 50 + i * 20, _T(ser_temp_student_id));//输出id
						_itoa_s(stu_score_vec_view[i].math, ser_temp_math, 10);
						outtextxy(430, 50 + i * 20, _T(ser_temp_math));//输出数学
						_itoa_s(stu_score_vec_view[i].english, ser_temp_english, 10);
						outtextxy(471, 50 + i * 20, _T(ser_temp_english));//输出英语
						_itoa_s(stu_score_vec_view[i].programming, ser_temp_programming, 10);
						outtextxy(512, 50 + i * 20, _T(ser_temp_programming));//输出编程
						_itoa_s(stu_score_vec_view[i].physics, ser_temp_physics, 10);
						outtextxy(553, 50 + i * 20, _T(ser_temp_physics));//输出物理
					}
					outtextxy(285, 70 + (i - 1) * 20, _T("查询到"));
					outtextxy(335, 70 + (i - 1) * 20, _T(char(stu_score_vec_view.size() + 48)));
					outtextxy(350, 70 + (i - 1) * 20, _T("行数据！"));
				}
			}
		}
	}
	return;
}
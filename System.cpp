#include <mylib.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>


#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_TAB 9
#define KEY_ESC 27
#define KEY_DOWN 80+256
#define KEY_UP 72+256
#define KEY_LEFT 75+256
#define KEY_RIGHT 77+256
#define KEY_DELETE 83+256
#define KEY_INSERT 82+256
#define KEY_F2 60+256
#define KEY_F5 63+256
#define KEY_PAGEUP 73
#define KEY_PAGEDOWN 81

#define BLACK 0
#define BLUE 1
#define GREEEN 2
#define CYAN 3
#define RED 4
#define GRAY 8
#define YELLOW 14
#define WHITE 15
#define BG_HEADER 4

#define so_item 8
#define dong 11
#define cot 40
#define TOADOX 10
#define TOADOY 2
#define HEIGHT_HEADER 3
#define WIDTH_MENU_BAR 14
#define SCREEN_WIDTH 100
#define SCREEN_HEIGTH 25
#define HEIGHT_FOOTER 3
#define WIDTH_BODY SCREEN_WIDTH-WIDTH_MENU_BAR
#define HEIGHT_BODY SCREEN_HEIGTH-HEIGHT_HEADER-HEIGHT_FOOTER

//vi tri dat form input
#define TOADOY_FORM 12
#define WIDTH_MESSAGE 50
#define TABLE_COLUMN_WIDTH 20


//KICH THUOC BANG
#define MAX 100
#define MAX_TEXT_INPUT 40
#define TEXT_ERROR 12
#define WIDTH_INPUT_TEXT 42



struct Date{
	int ngay;
	int thang;
	int nam;
};

int keyPressed(){
	int a = getch();
	if(a == 0 || a== 224){
		a = 256 + getch();
	}
	return a;
}

void veHinhChuNhat(int toaDoX, int toaDoY, int chieuDai, int chieuRong, int color){
	SetBGColor(color);
	for(int i = 0; i < chieuRong; i++){
		gotoxy(toaDoX, toaDoY + i);
		for(int j = 0; j < chieuDai; j++){
			cout <<" ";
		}
	}
	SetBGColor(BLACK);	
}

int nhapChuoiKiTuVaSo(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0'&& c <= '9' || c== KEY_SPACE) && chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_DELETE && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT &&c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F2 && c != KEY_F5) ;
	return c;
}

int nhapChuoiKiTu(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'|| c == KEY_SPACE)&& chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_DELETE && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F2 && c != KEY_F5) ;
	return c;
}

int nhapChuoiKiTuSo(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if(c >= '0'&& c <= '9' && chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_DELETE && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F2);
	return c;
}

int nhapKyTu(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDai = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c= keyPressed();
		if(c == '1' || c == '0' &&  chieuDai < maxLengthText){
			gotoxy(toaDoX + chieuDai, toaDoY);
			cout << (char)c;
			chieuDai++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDai != 0){
			gotoxy(toaDoX + --chieuDai, toaDoY);
			cout << " ";
			s.erase(chieuDai);
			gotoxy(toaDoX + chieuDai, toaDoY);
		}
	}while(c != KEY_ENTER && c != KEY_DELETE && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F2);
	return c;
}

int nhapKyTuNhapXuat(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDai = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c= keyPressed();
		if((c == 'n' || c == 'N' || c == 'x' || c == 'X')&&  chieuDai < maxLengthText){
			gotoxy(toaDoX + chieuDai, toaDoY);
			cout << (char)c;
			chieuDai++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDai != 0){
			gotoxy(toaDoX + --chieuDai, toaDoY);
			cout << " ";
			s.erase(chieuDai);
			gotoxy(toaDoX + chieuDai, toaDoY);
		}
	}while(c != KEY_ENTER && c != KEY_DELETE && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F2 && c != KEY_F5);
	return c;
}

int kiemTraHopLeChuoiSoThuc(string s){
	int dem = 0;
	for(int i = 0; i < s.length(); i++)
		if(s[i] == '.') dem++;
	return dem <= 1;
}

void veKhungDanhSach(int soCot, int soHang, int toaDoX, int toaDoY){
	for (int i = 0; i <= soHang * 2; i++){
		gotoxy(toaDoX, toaDoY + i);
		if (i % 2 == 0)
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		
		if (i == 0 && j == 0)cout << char(218);
		else if (i == 0 && j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(191);
		else if (j == 0 && i == soHang * 2) cout << char(192);
		else if (i == soHang * 2 && j == soCot * TABLE_COLUMN_WIDTH + soCot)cout << char(217);
		else if (j == 0) cout << char(195);
		else if (j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(180);
		else if (i == 0 && j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(194);
		else if (i == soHang * 2 && j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(193);
		else if (j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(197);
		else cout << char(196);
		
		else
		
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		if (j % (TABLE_COLUMN_WIDTH + 1) == 0)
			cout << (char)179;
		else
			cout << " ";
	}
}

void veLaiGoc(int toaDoX, int toaDoY, int soDong){
	for(int i = 0; i <= soDong * 2; i++){
		if(i % 2 == 0){
			if(i == 0)
			{
				gotoxy(toaDoX + 5, toaDoY);
				cout << (char) 194;	
			}
			else if(i == soDong * 2){
				gotoxy(toaDoX + 5, toaDoY + soDong * 2);
				cout << (char )193;
			}
			else {
				gotoxy(toaDoX + 5, toaDoY + i);
				cout << (char) 197;
			}
			
					
		}
	}
}

void veInputText(int toaDoX, int toaDoY){
	// 218 --- 196 --- 191
	// 179 ----------- 179
	// 192 --- 196 --- 217
	SetColor(WHITE);
	SetBGColor(BLACK);
	
	gotoxy(toaDoX, toaDoY);
	cout << char (218);
	for (int i = 1; i < WIDTH_INPUT_TEXT; i++) cout << char (196);
	cout << char (191);
	
	gotoxy(toaDoX, toaDoY + 1);
	cout << char (179);
	gotoxy(toaDoX + WIDTH_INPUT_TEXT, toaDoY + 1);
	cout << char (179);
	
	gotoxy(toaDoX, toaDoY + 2);
	cout << char (192);
	for (int i = 1; i < WIDTH_INPUT_TEXT; i++) cout << char (196);
	cout << char (217);
}

void veChuThich(){
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(13, 28);
	cout << "ESC: Thoat \t INSERT: Hieu chinh \t DELETE: Xoa \t <-Trang truoc \t Trang sau->";
}

string chuyenSoThanhChuoi(int num){
    string s = "";
	while (num != 0){
		s = char((num % 10) + 48) + s;
		num = num / 10;
	}
	if (s.length() < 2) s = '0' + s;
	return s;
}

string to_string(int num){
	if(num == 0) return "0";
	string s = "";
	while(num != 0){
		s = char((num % 10) + 48) + s;
		num /= 10;
	}
	return s;
}

string chuyenNgayThanhChuoi(Date d){
	string s = "";
	string temp = "";
	temp = chuyenSoThanhChuoi(d.ngay);
	s += temp + "/";
	temp = chuyenSoThanhChuoi(d.thang);
	s += temp + "/";
	temp = chuyenSoThanhChuoi(d.nam);
	s += temp;
	return s;
}

Date HamTraVeCurrentTime(){
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	Date d;
	d.ngay = aTime->tm_mday;
	d.thang = aTime->tm_mon + 1;
	d.nam = aTime->tm_year + 1900;
	return d;
}

int kiemTraHopLeNgayThangNhapVao(int ngay, int thang, int nam){
	Date tgHienTai;
	tgHienTai = HamTraVeCurrentTime();
	
	if (nam > tgHienTai.nam) {
		return 0;
	} else if (thang <= 0 || thang > 12 || (nam == tgHienTai.nam && thang > tgHienTai.thang)) {
		return 0;
	} else if (nam == tgHienTai.nam && thang == tgHienTai.thang && ngay > tgHienTai.ngay) {
		return 0;
	}
	
	switch(thang){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(ngay <=0 || ngay > 31) {
				return 0;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(ngay <= 0 || ngay > 30) {
				return 0;
			}
			break;
		case 2:
			if((nam % 4 == 0 && (ngay <= 0 || ngay > 29)) || (nam % 4 != 0 && (ngay <= 0 || ngay > 28))) {
				return 0;
			}
			break;	
	}
	
	return 1;
}

int kiemTraNgayGiua2Ngay(Date ngayBatDau, Date ngayKetThuc, Date ngayKiemTra){
	if(ngayKiemTra.nam < ngayBatDau.nam || ngayKiemTra.nam > ngayKetThuc.nam) return 0;
	
	if(ngayKiemTra.nam == ngayBatDau.nam){
		if(ngayKiemTra.thang < ngayBatDau.thang) return 0;
		if(ngayKiemTra.thang == ngayBatDau.thang && ngayKiemTra.ngay < ngayBatDau.ngay) return 0;		
	}
	
	if(ngayKiemTra.nam == ngayKetThuc.nam){
		if(ngayKiemTra.thang > ngayKetThuc.thang) return 0;
		if(ngayKiemTra.thang == ngayBatDau.thang && ngayKiemTra.ngay > ngayKetThuc.ngay) return 0;
	}
		return 1;
}

int soSanhThoiGian(Date BD, Date KT){
	if (BD.nam > KT.nam) return 1;
	else if (BD.nam < KT.nam) return -1;
	else {
		if (BD.thang > KT.thang) return 1;
		else if (BD.thang < KT.thang) return -1;
		else {
			if (BD.ngay > KT.ngay) return 1;
			else if (BD.ngay < KT.ngay) return -1;
			else return 0;
		}
	}
}

int hopThoaiLuaChon(string message, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	veHinhChuNhat(toaDoX, toaDoY, chieuDai, chieuRong, RED);
	gotoxy(toaDoX + (chieuDai - message.length())/2, toaDoY + chieuRong / 2 - 1);
	SetBGColor(RED);
	SetColor(WHITE);
	cout << message;
	gotoxy(WIDTH_MENU_BAR + (WIDTH_BODY - message.length()) / 2 + message.length() + 5, toaDoY + chieuRong / 2 - 1);
	char c;
	int res = 0;
	do{
		c= keyPressed();
		if((c == 'y') || c == 'Y' )  {
			cout << c;
			return 1;
		}
		else if((c == 'n') || c == 'N') {
			cout << c;
			return 0;
		}
	}while(c != 'y' && c != 'Y' && c != 'n' && c != 'N' && c != KEY_ESC);
	if(c == KEY_ESC) return 0;
}

int kiemTraChuoiNhapVao(string s){
	for(int i = 0; i < s.length(); i++){
		if(s[i] !=' ') return 1;
	}
	return 0;
}

string dinhDangChuoiNhapVao(string s){
	string chuoi = "";
	string temp = "";
	for(int i = 0; i < s.length(); i++){
		if(s[i] != ' ' && s[i] != KEY_TAB){
			temp += s[i];
		}else{
			if(temp.length() > 0){
				chuoi += temp + " ";
				temp = "";
			}
		}
	}
	if(temp.length() > 0)
		return chuoi += temp;
	else return chuoi.erase(chuoi.length()-1);
}

void Normal () {
	SetColor(15);
	SetBGColor(0);
}

void HighLight () {
	SetColor(15);
	SetBGColor(1);
}

bool kiemTraChuoiCoKhoangTrang(string s){
	for(int i = 0; i < s.length(); i++){
		if(s[i] == ' ') return true;
	}
	return false;
}

void thongBao(string message, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	veHinhChuNhat(toaDoX, toaDoY, chieuDai, chieuRong, BG_HEADER);
	gotoxy(toaDoX + (chieuDai - message.length())/2, toaDoY + chieuRong / 2);
	SetBGColor(BG_HEADER);
	SetColor(WHITE);
	cout << message;
	getch();
}

string chuyenChuoiThanhChuoiHoa(string s){
	for(int i = 0; i < s.length(); i++){
		s[i] = toupper(s[i]);
	}
	return s;
}

void veBangDanhSach(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetColor(WHITE);
	SetBGColor(BLACK);

	// Tao bang
	// 218 --- 196 --- 194 --- 196 --- 191
	// 179             179             179
	// 195 --- 196 --- 197 --- 196 --- 180
	// 179             179             179
	// 192 --- 196 --- 193 --- 196 --- 217
	
	for (int i = 0; i < soDong * 2 + 1; i++){
		gotoxy(toaDoX, toaDoY + i);
		for (int j = 0; j < soCot * 2 + 1; j++) {
			// Dong dau
			if (i == 0){
				if (j == 0) cout << char (218);
				else if (j == soCot * 2) cout << char (191);
			 	else if (j % 2 == 0) cout << char (194);
				else for (int k = 0; k < kichThuocO; k++) cout << char (196);
			}	
				
			// Dong cuoi
			else if (i == soDong * 2){
				if (j == 0) cout << char (192);
				else if (j == soCot * 2) cout << char (217);
				else if (j % 2 == 0) cout << char (193);
				else for (int k = 0; k < kichThuocO; k++) cout << char (196);
			}
			
			// Dong Giua
			else {
				if (i % 2 == 0) {
					if (j == 0) cout << char (195);
					else if (j == soCot * 2) cout << char (180);
					else if (j == 0 || j == soCot * 2) cout << char (179);
					else if (j % 2 == 0) cout << char (197);
					else for (int k = 0; k < kichThuocO; k++) cout << char (196);
				}
				else if (j % 2 == 0) cout << char (179);
				else for (int k = 0; k < kichThuocO; k++) cout << " ";
			}
				
		}	
	}
}
void BaoLoi(string s){
	int x = wherex();
	int y = wherey();
	gotoxy(45, y + 3);
	cout << s;
	Sleep(2000);
	gotoxy(45, y + 3);
	for(int i = 0; i <s.length(); i++)
		cout << " ";
	gotoxy(x, y);
}


#include "DuLieu.cpp"

string tenCotBangVatTu[SIZE_BANG_DANH_SACH_VT] = {"STT", "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG TON"};
string thuocTinhVatTu[SIZE_THUOC_TINH_VT] = {"Ma Vat Tu", "Ten Vat Tu", "Don Vi Tinh", "So Luong Ton"};
int kiemTraRongVatTu(DSVatTu &ds_VT){
	return (ds_VT.soLuongVatTu == 0 ? 1 : 0);
}

int kiemTraDayVatTu(DSVatTu &ds_VT){
	return (ds_VT.soLuongVatTu == MAX ? 1 : 0);
}

int timViTriVatTuTrung(DSVatTu &ds_VT, string maVT){
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		if(ds_VT.nodesVT[i].maVatTu == maVT)
			return i;
	}
	return -1;
}

int timViTriThemVatTu(DSVatTu ds_VT, string maVT){
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		if(ds_VT.nodesVT[i].maVatTu == maVT)	return -1;
		if(ds_VT.nodesVT[i].maVatTu > maVT)		return i;
	}
	return ds_VT.soLuongVatTu;
}

int themVatTuVaoViTri(DSVatTu &ds_VT, VatTu vatTu){
	int index = timViTriThemVatTu(ds_VT, vatTu.maVatTu);
	if(index < 0 || index > ds_VT.soLuongVatTu || kiemTraDayVatTu(ds_VT) == 1)   
		return 0;      
	
	for(int j = ds_VT.soLuongVatTu; j > index; j--){
		ds_VT.nodesVT[j] = ds_VT.nodesVT[j-1];
	}
	ds_VT.nodesVT[index] = vatTu;
	ds_VT.soLuongVatTu++;
	return 1;
}
// Trc khi xoa vat tu: kiem tra xem co hoa don nao ton tai ma VT ko?
int xoaVatTu(DSVatTu &ds_VT, string maVT){
	int index = timViTriVatTuTrung(ds_VT, maVT);
	if(index < 0 || index >= ds_VT.soLuongVatTu || kiemTraRongVatTu(ds_VT))
		return 0;
	for(int i = index; i < ds_VT.soLuongVatTu - 1; i++)
		ds_VT.nodesVT[i] = 	ds_VT.nodesVT[i + 1];
	ds_VT.soLuongVatTu--;
	return 1;
}

void sapXepTenVatTuTangDan(DSVatTu &ds_VT){
	for(int i = 0; i < ds_VT.soLuongVatTu - 1; i++){
		for (int j = i + 1; j < ds_VT.soLuongVatTu; j++){
			if(ds_VT.nodesVT[i].tenVatTu > ds_VT.nodesVT[j].tenVatTu){
				VatTu t = ds_VT.nodesVT[i];
				ds_VT.nodesVT[i] = ds_VT.nodesVT[j];
				ds_VT.nodesVT[j] = t;
			}
		}
	}
}

void saveFileVatTu(DSVatTu &ds_VT){
	ofstream myFile;
	myFile.open("dsVatTu.txt", ios::out);
	
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		VatTu vt = ds_VT.nodesVT[i];
		myFile << vt.maVatTu << endl;
		myFile << vt.tenVatTu << endl;
		myFile << vt.donViTinh << endl;
		myFile << vt.soLuongTon;
		if(i == ds_VT.soLuongVatTu - 1)
			continue;
		myFile << endl;
	}
	myFile.close();
}

void loadFileVatTu(DSVatTu &ds_VT){
	ifstream myFile;
	myFile.open("dsVatTu.txt");
	if(!myFile){
		ds_VT.soLuongVatTu = 0;
		return;
	}
	string slt =""; 
	VatTu vt;
//int dem = 0;
	while(!myFile.eof()){
		getline(myFile, vt.maVatTu);
		getline(myFile, vt.tenVatTu);
		getline(myFile, vt.donViTinh);
		getline(myFile, slt);
		stringstream(slt) >> vt.soLuongTon;
		
		themVatTuVaoViTri(ds_VT, vt);
		//dem++;
	}
	//ds_VT.soLuongVatTu = dem;
	myFile.close();
}


//int main(){
//	char tenFile[] = "dsVatTu.txt";
//	DSVatTu dsvt;
//	dsvt.soLuongVatTu = 0;
//	VatTu vt1;
//	vt1.maVatTu = "D01";
//	vt1.tenVatTu = "Den Loai 1";
//	vt1.donViTinh = "Cai";
//	vt1.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt1);
//	VatTu vt2;
//	vt2.maVatTu = "D02";
//	vt2.tenVatTu = "Den Loai 2";
//	vt2.donViTinh = "Cai";
//	vt2.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt2);
//	VatTu vt3;
//	vt3.maVatTu = "D03";
//	vt3.tenVatTu = "Den Loai 3";
//	vt3.donViTinh = "Cai";
//	vt3.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt3);
//	VatTu vt4;
//	vt4.maVatTu = "D04";
//	vt4.tenVatTu = "Den Loai 4";
//	vt4.donViTinh = "Cai";
//	vt4.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt4);
//	VatTu vt5;
//	vt5.maVatTu = "G01";
//	vt5.tenVatTu = "Gach Loai 1";
//	vt5.donViTinh = "Vien";
//	vt5.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt5);
//	VatTu vt6;
//	vt6.maVatTu = "G02";
//	vt6.tenVatTu = "Gach Loai 2";
//	vt6.donViTinh = "Vien";
//	vt6.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt6);
//	VatTu vt7;
//	vt7.maVatTu = "G03";
//	vt7.tenVatTu = "Gach Loai 3";
//	vt7.donViTinh = "Vien";
//	vt7.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt7);
//	VatTu vt8;
//	vt8.maVatTu = "G04";
//	vt8.tenVatTu = "Gach Loai 4";
//	vt8.donViTinh = "Vien";
//	vt8.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt8);
//	VatTu vt9;
//	vt9.maVatTu = "X01";
//	vt9.tenVatTu = "Xi Mang Loai 1";
//	vt9.donViTinh = "Bao";
//	vt9.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt9);
//	VatTu vt11;
//	vt11.maVatTu = "X02";
//	vt11.tenVatTu = "Xi Mang Loai 2";
//	vt11.donViTinh = "Bao";
//	vt11.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt11);
//	VatTu vt12;
//	vt12.maVatTu = "X03";
//	vt12.tenVatTu = "Xi Mang Loai 3";
//	vt12.donViTinh = "Bao";
//	vt12.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt12);
//	VatTu vt13;
//	vt13.maVatTu = "X04";
//	vt13.tenVatTu = "Xi Mang Loai 4";
//	vt13.donViTinh = "Bao";
//	vt13.soLuongTon = 300;			
//themVatTuVaoViTri(dsvt, vt13);
//	VatTu vt14;
//	vt14.maVatTu = "S01";
//	vt14.tenVatTu = "Son Loai 1";
//	vt14.donViTinh = "Thung";
//	vt14.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt14);
//	VatTu vt15;
//	vt15.maVatTu = "S02";
//	vt15.tenVatTu = "Son Loai 2";
//	vt15.donViTinh = "Thung";
//	vt15.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt15);
//	VatTu vt16;
//	vt16.maVatTu = "S03";
//	vt16.tenVatTu = "Son Loai 3";
//	vt16.donViTinh = "Thung";
//	vt16.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt16);
//	VatTu vt17;
//	vt17.maVatTu = "S04";
//	vt17.tenVatTu = "Son Loai 4";
//	vt17.donViTinh = "Thung";
//	vt17.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt17);
//	saveFileVatTu(dsvt, tenFile);
//	xoaVatTu(dsvt, "A");
//	sapXepTenVatTuTangDan(dsvt);
//	loadFileVatTu(dsvt, tenFile);
//	cout << dsvt.soLuongVatTu << endl;
//	cout << "Ma" << "\tTen" << "\t\tDon Vi Tinh" << "\tSo Luong Ton" << endl;
//	for(int i = 0; i < dsvt.soLuongVatTu; i++){
//		cout << dsvt.nodesVT[i].maVatTu  << "\t" << dsvt.nodesVT[i].tenVatTu << "\t\t" << dsvt.nodesVT[i].donViTinh << "\t" << dsvt.nodesVT[i].soLuongTon << endl;
//	}
//	
//	return 0;
//}


int tongSoTrangVatTu(DSVatTu &dsVT){
	return dsVT.soLuongVatTu / SL_VAT_TU_TRONG_TRANG + (dsVT.soLuongVatTu % SL_VAT_TU_TRONG_TRANG == 0 ? 0 : 1);
}
void veGiaoDienThemVatTu(){
	Normal();
	// Xoa noi dung trong body
	for (int i = 0; i < HEIGHT_BODY; i ++)
		for (int j = 0; j < WIDTH_BODY; j++){
			gotoxy(TOADOX+WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
		
	// Tieu De
	veHinhChuNhat(45, 4, 26, 3, RED);
	SetBGColor(4);
	gotoxy(52, 5);
	cout << "THEM VAT TU";
	Normal();
	// Nhap thong tin vat tu
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < SIZE_THUOC_TINH_VT; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		cout << thuocTinhVatTu[i];
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	// Ve Footer
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
//	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
//		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
//		for (int j = 0; j < WIDTH_BODY; j++){
//			cout << " ";
//		}
//	}
	gotoxy(46, 25);
	cout << "ESC: Tro ve \t F5: Luu";
}

int themMoiVatTu(DSVatTu &dsVatTu){
	veGiaoDienThemVatTu();
	
	VatTu vt;
	int c;
	int viTriNhapLieu = 0;
	string soLuongStr = "";
	string maVT = "";
	string errors [4] = {"", "", "", ""};
	
	
	int toaDoXNhan = 25;//TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = 9;//0OADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 16;
	int toaDoYInputText = toaDoYNhan ;
	
	do {
		switch (viTriNhapLieu){
			// Nhap MAVT
			case 0:
				c = nhapChuoiKiTuVaSo(vt.maVatTu, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3, WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				// Kiem tra MAVT: Rong & co ky tu khoang trang ko?
				if (vt.maVatTu.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
					//Kiem tra MAVT co trung ko?
				}else if (timViTriVatTuTrung(dsVatTu, chuyenChuoiThanhChuoiHoa(vt.maVatTu)) > -1){
					// Noi dung thong bao
					//cout << timViTriVatTuTrung(dsVatTu, vt.maVatTu);
					errors[viTriNhapLieu] = "Ma " + chuyenChuoiThanhChuoiHoa(vt.maVatTu) + " da ton tai!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
					// Kiem tra MAVT co ' ' ko ?
				} else if (kiemTraChuoiCoKhoangTrang(vt.maVatTu)){
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc co ky tu khoang trang!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				} else {
//					vt.maVatTu = maVT;
//					maVT = "";
					errors[viTriNhapLieu] = "";
				}
				
				break;
				
			// Nhap TENVT
			case 1:	
				c = nhapChuoiKiTuVaSo(vt.tenVatTu, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
					// Kiem tra rong
				if (vt.tenVatTu.length() <= 0) {	
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
					
				break;
				
			// Nhap DVT
			case 2:	
				c = nhapChuoiKiTuVaSo(vt.donViTinh, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
				if (vt.donViTinh.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
				
				break;
			
			// Nhap SOLUONGTON
			case 3:	
				c = nhapChuoiKiTuSo(soLuongStr, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
				if (soLuongStr.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				} else errors[viTriNhapLieu] = "";
				
				break;
		}
		
		if ((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < SIZE_THUOC_TINH_VT - 1) viTriNhapLieu++;
		
		if (c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F5){
			if (vt.maVatTu.length() > 0 && vt.tenVatTu.length() > 0 && vt.donViTinh.length() > 0 && soLuongStr.length() > 0) {
				stringstream(soLuongStr) >> vt.soLuongTon;
				themVatTuVaoViTri(dsVatTu, vt);
				
				saveFileVatTu(dsVatTu);
				
				string noiDungThongBao = "Them thanh cong: " + vt.maVatTu + " - " + vt.tenVatTu;
				thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
			
				return timViTriVatTuTrung(dsVatTu, vt.maVatTu);
			}	
		}
		
	} while (c != KEY_ESC);
	
	return -1;
}
void veGiaoDienCapNhatThongTinVatTu(){
	SetColor(YELLOW);
	SetBGColor(BLACK);
	
	// Xoa noi dung trong body
	for (int i = 0; i < HEIGHT_BODY; i ++)
		for (int j = 0; j < WIDTH_BODY; j++){
			gotoxy(TOADOX+WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
		
	// Tieu De
	string tieuDe = "CAP NHAT THONG TIN VAT TU";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - tieuDe.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << tieuDe;
	
	// Nhap thong tin vat tu
	int toaDoXNhan = TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = TOADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < SIZE_THUOC_TINH_VT; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		cout << thuocTinhVatTu[i];
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	// Ve Footer
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	string strHuongDan = "ESC: Tro ve \t F5: Luu";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-strHuongDan.length())/2, SCREEN_HEIGTH );
	cout << strHuongDan;
}

void veKhungDanhSachVatTu(){
	Normal();
	system("cls");
	// In tieu de
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DANH SACH VAT TU";
	veBangDanhSach(13, 4, 1, 11, 6);
	veKhungDanhSach(4, 11, 18, 4);
	veLaiGoc(13, 4, 11);
	veChuThich();
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < SIZE_BANG_DANH_SACH_VT; i++){
		if(i == 0){
			toaDoXNhan = 15;
		}
		else toaDoXNhan =  19 + (TABLE_COLUMN_WIDTH - tenCotBangVatTu[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangVatTu[i];
	}
	Normal();
}

//void doDuLieuRaBangVatTu(DSVatTu &dsVT, int tongTrang, int trang){
//	// Xoa du lieu trong bang
//	//xoaDuLieuTrongBangDanhSachVatTu(toaDoX, toaDoY, soCot, soDong, TABLE_COLUMN_WIDTH);
//	
//	// Ghi du lieu moi vao bang
//	SetColor(BLACK);	
//	int toaDoXCuaConTro;
//	int toaDoYCuaConTro;	
//	int vtDau = (trang - 1) * SL_VAT_TU_TRONG_TRANG;	
//	int tam = 0;
//	string str;
//	
//	for (int i = vtDau; i < trang * SL_VAT_TU_TRONG_TRANG && i < dsVT.soLuongVatTu; i++){
//		
//		toaDoYCuaConTro = toaDoY + 3 + 2 * tam;
//		tam++;
//		
//		// IN STT
//		str = chuyenSoThanhChuoi(i + 1);
//		toaDoXCuaConTro = 16;
//		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
//		cout << str;
//		
//		// IN MAVT
//		toaDoXCuaConTro = 19 + (TABLE_COLUMN_WIDTH - dsVT.nodesVT[i].maVatTu.length())/2 + 21 * (i-1);
//		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
//		cout << dsVatTu.NODE[i].MAVT;
//		
//		// IN TENVT
//		toaDoXCuaConTro = toaDoX + 2 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[i].TENVT.length()) / 2;
//		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
//		cout << dsVatTu.NODE[i].TENVT;
//		
//		// IN DVT
//		toaDoXCuaConTro = toaDoX + 3 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[i].DVT.length()) / 2;
//		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
//		cout << dsVatTu.NODE[i].DVT;
//		
//		// IN SOLUONGTON
//		str = chuyenSoThanhChuoi(dsVatTu.NODE[i].SOLUONGTON);
//		toaDoXCuaConTro = toaDoX + 4 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
//		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
//		cout << dsVatTu.NODE[i].SOLUONGTON;
//	
//	}
//	
//	// phan trang
//	SetColor(RED);
//	SetBGColor(BG_BODY);
//	string strTrang = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
//	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - strTrang.length()) / 2, TOADOY + HEIGHT_HEADER + HEIGHT_BODY - 3);
//	cout << strTrang;
//}

void xoaDuLieuTrongBangVatTu(){
	
}
int main(){
	DSVatTu dsVT;
	dsVT.soLuongVatTu = 0;
	loadFileVatTu(dsVT);
	themMoiVatTu(dsVT);
	
	return 0;
}

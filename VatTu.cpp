#include "DuLieu.cpp"

string tenCotBangVatTu[5] = {"STT", "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG TON"};
string thuocTinhVatTu[4] = {"Ma Vat Tu", "Ten Vat Tu", "Don Vi Tinh", "So Luong Ton"};
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

int soLuongVatTuTonKho(DSVatTu &dsVT){
	int dem = 0;
	for(int i = 0; i < dsVT.soLuongVatTu; i++){
		if(dsVT.nodesVT[i].soLuongTon > 0)
			dem++;
	}
	return dem;
}

int tongSoTrangVatTu(DSVatTu &dsVT){
	return dsVT.soLuongVatTu / 10 + (dsVT.soLuongVatTu % 10 == 0 ? 0 : 1);
}

void veGiaoDienThemVatTu(){
	Normal();
		
	veHinhChuNhat(45, 4, 26, 3, RED);
	SetBGColor(4);
	gotoxy(52, 5);
	cout << "THEM VAT TU";
	Normal();

	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < 4; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		SetColor(YELLOW);
		cout << thuocTinhVatTu[i];
		Normal();
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}

	gotoxy(46, 25);
	cout << "ESC: Tro ve \t F2: Luu";
}

void themMotVatTu(DSVatTu &dsVatTu){
First:	
	SetBGColor(BLACK);
	SetColor(WHITE);
	system("cls");
	veGiaoDienThemVatTu();
	
	VatTu vt;
	int c;
	int viTriNhapLieu = 0;
	string soLuongStr = "";
	string errors [4] = {"", "", "", ""};
	
	
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = toaDoXNhan + 16;
	int toaDoYInputText = toaDoYNhan ;
	
	do {
		switch (viTriNhapLieu){
			// Nhap MAVT
			case 0:
				c = nhapChuoiKiTuVaSo(vt.maVatTu, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3, WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if (vt.maVatTu.length() <= 0) {
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else if (timViTriVatTuTrung(dsVatTu, chuyenChuoiThanhChuoiHoa(vt.maVatTu)) > -1){
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
		
		if(c == KEY_F2){
			if (vt.maVatTu.length() > 0 && vt.tenVatTu.length() > 0 && vt.donViTinh.length() > 0 && soLuongStr.length() > 0) {
				stringstream(soLuongStr) >> vt.soLuongTon;
				vt.maVatTu = chuyenChuoiThanhChuoiHoa(vt.maVatTu);
				themVatTuVaoViTri(dsVatTu, vt);
				
				saveFileVatTu(dsVatTu);
				
				thongBao("Them thanh cong!!", 45, 12, 27, 3);
				goto First;
				//return timViTriVatTuTrung(dsVatTu, vt.maVatTu);
			}	
		}
		if(c == KEY_ESC) {
			system("cls");
			break;
		}
	} while (1);
	
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
	for (int i = 0; i < 5; i++){
		if(i == 0){
			toaDoXNhan = 15;
		}
		else toaDoXNhan =  19 + (TABLE_COLUMN_WIDTH - tenCotBangVatTu[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangVatTu[i];
	}
	Normal();
}

void xoaDuLieuTrongBangVatTu(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	int j = 7;
	// XOA stt
	for(int i = 0; i < 10; i++){
		gotoxy(14, j);
		cout << "    ";
		j += 2;
	}
	// Xoa MA VT
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(19, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa ten VT
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(40, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa dvt
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(82, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa slt
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(61, j);
		cout << "                    ";
		j += 2;
	}
}

void doDuLieuRaBangVatTu(DSVatTu &dsVT, int tongTrang, int trang){
	xoaDuLieuTrongBangVatTu();
	
	// Ghi du lieu moi vao bang
	SetColor(WHITE);	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;	
	int vtDau = (trang - 1) * 10;	
	string str;
	int hang = 7;
	sapXepTenVatTuTangDan(dsVT);
	// STT
	for(int i = vtDau; i < trang * 10 && i < dsVT.soLuongVatTu; i++){
		gotoxy(15, hang);
		str = chuyenSoThanhChuoi(i + 1);
		cout << str;
		hang += 2;
	}
	// MaVT
	hang = 7;
	for(int i = vtDau; i < trang * 10 && i < dsVT.soLuongVatTu; i++){
		toaDoXCuaConTro = 19 + (20 - dsVT.nodesVT[i].maVatTu.length())/2 ;
		gotoxy(toaDoXCuaConTro, hang);
		cout << dsVT.nodesVT[i].maVatTu;
		hang += 2;
	}
	
	// TenVT
	hang = 7;
	for(int i = vtDau; i < trang * 10 && i < dsVT.soLuongVatTu; i++){
		toaDoXCuaConTro = 36 + (20 - dsVT.nodesVT[i].maVatTu.length())/2 ;
		gotoxy(toaDoXCuaConTro, hang);
		cout << dsVT.nodesVT[i].tenVatTu;
		hang += 2;
	}
	//DVT
	hang = 7;
	for(int i = vtDau; i < trang * 10 && i < dsVT.soLuongVatTu; i++){
		toaDoXCuaConTro = 61 + (20 - dsVT.nodesVT[i].donViTinh.length())/2 ;
		gotoxy(toaDoXCuaConTro, hang);
		cout << dsVT.nodesVT[i].donViTinh;
		hang += 2;
	}
	//SLT
	hang = 7;
	for(int i = vtDau; i < trang * 10 && i < dsVT.soLuongVatTu; i++){
		toaDoXCuaConTro = 90 ;
		gotoxy(toaDoXCuaConTro, hang);
		cout << dsVT.nodesVT[i].soLuongTon;
		hang += 2;
	}
	
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(81,2);
	cout << page;
}

void suaVatTu(DSVatTu &dsVT, VatTu vt){
	system("cls");
	int c;
	int viTriNhapLieu = 1;
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = toaDoXNhan + 16;
	int toaDoYInputText = toaDoYNhan ;

	veGiaoDienThemVatTu();
	
	SetColor(YELLOW);
	gotoxy(41, 9);
	cout << vt.maVatTu;
	gotoxy(41, 18);
	cout << vt.soLuongTon;
	
	SetColor(WHITE);
	gotoxy(41, 12);
	cout << vt.tenVatTu;
	gotoxy(41, 15);
	cout << vt.donViTinh;
	
	string errors[2] = {"", ""};
	
	do {
		switch (viTriNhapLieu){
							
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
		}
		
		if (c == KEY_DOWN || c == KEY_ENTER) viTriNhapLieu = 2;
		
		if (c == KEY_UP) viTriNhapLieu = 1;
		
		if(c == KEY_F2){
			int viTri = timViTriVatTuTrung(dsVT, vt.maVatTu);
			if (viTri > -1 && vt.tenVatTu.length() > 0 && vt.donViTinh.length() > 0){
				
			 	dsVT.nodesVT[viTri] = vt;
				
				saveFileVatTu(dsVT);
				
				// Thong bao
				string noiDungThongBao = "Cap nhat thanh cong: ";
				thongBao(noiDungThongBao, 24 + (86 - noiDungThongBao.length()) / 2, 5 + 7, noiDungThongBao.length() + 10, 5);
				break;
			}
		}
	} while (c != KEY_ESC);	
	
}

int push(StackNV &sp, TreeNhanVien nv){
	StackNV p;
	p = new StackNhanVien;
	p->nodeNV = nv;
	p->next = sp;
	sp = p;
	return 1;
}

int pop(StackNV &sp, TreeNhanVien &nv){
	if(sp == NULL)
		return 0;
	StackNV p = sp;
	nv = p->nodeNV;
	sp = p->next;
	delete p;
	return 1; 
}

int thongBaoXoaVatTu(DSVatTu &dsVT, TreeNhanVien &rootNV, string maVT){
	StackNV stack = NULL;
	while(rootNV != NULL){
					
		PTRHoaDon ptrHD = rootNV->nhanVien.hoaDonFirst;
		while(ptrHD != NULL){
			PTR_CT_HoaDon ptrCtHD = ptrHD->hoaDon.CT_HD_First;
			while(ptrCtHD != NULL){
				if(ptrCtHD->chiTietHD.maVT == maVT){
					string noiDungThongBao2 = "Khong duoc phep xoa";
					thongBao(noiDungThongBao2,  WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao2.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao2.length() + 10, 5);
					return 0;			
				}
				ptrCtHD = ptrCtHD->CT_HD_Next;
			}
			ptrHD = ptrHD->HD_Next;
		}
		if(rootNV->nvRight != NULL)
			push(stack, rootNV->nvRight);
		if(rootNV->nvLeft != NULL)
			rootNV = rootNV->nvLeft;
		else if(stack == NULL)
			break;
			else pop(stack, rootNV);
	}
	
	int vtVatTuXoa = timViTriVatTuTrung(dsVT, maVT);
	if (vtVatTuXoa > -1){
		VatTu vt = dsVT.nodesVT[vtVatTuXoa];
		string noiDungThongBao1 = "Ban co muon xoa " + vt.maVatTu + " - " + vt.tenVatTu + " khong?(y/n):";
		
		int xacNhanXoa = hopThoaiLuaChon(noiDungThongBao1,  WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao1.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5)/2, noiDungThongBao1.length() + 10, 5 );
		if(xacNhanXoa == 1){
			xoaVatTu(dsVT, vt.maVatTu);
			saveFileVatTu(dsVT);
			
			// Thong bao
			string noiDungThongBao2 = "Da xoa Vat tu!";
			thongBao(noiDungThongBao2,  WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao1.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao1.length() + 10, 5);
			
			return 1;
		}
	}
	return 0;
	
}

void giaoDienVatTu(DSVatTu &dsVT, TreeNhanVien &rootNV){	
	if (kiemTraRongVatTu(dsVT)){
		string noiDungThongBao = "Danh sach Vat Tu rong!";
		thongBao(noiDungThongBao, 48, 2, noiDungThongBao.length() + 10, 3);	
 
	} else {
		int trang = 1;
		int tongTrang = tongSoTrangVatTu(dsVT);
		int vtLuaChon = 1;
		int c;
		string s;
		
		int soCot = SIZE_BANG_DANH_SACH_VT;
		int soDong = SL_VAT_TU_TRONG_TRANG ;
		int toaDoX = 10;
		int toaDoY = 7;
		
		veKhungDanhSachVatTu();
		doDuLieuRaBangVatTu(dsVT, tongTrang, trang);	
		// Ve con tro
		gotoxy(toaDoX, toaDoY);
		cout << "->";
		
		do {
			c = keyPressed();
			
			// CHUYEN VI TRI CON TRO
			if (c == KEY_UP){
				if (vtLuaChon > 1){
					// Xoa con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon--;
					// Ve con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			} else if (c == KEY_DOWN){
				if (vtLuaChon < SL_VAT_TU_TRONG_TRANG && (vtLuaChon + (trang - 1) * 10) < dsVT.soLuongVatTu ) 
				{
					// Xoa con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon++;
					// Ve con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			
			// CHUYEN TRANG
			} else if(c == KEY_LEFT) {
				if (trang > 1){
					trang--;	

					// Nap du lieu vao ban
					xoaDuLieuTrongBangVatTu();
					doDuLieuRaBangVatTu(dsVT, tongTrang, trang);	
					
					// Xoa con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			} else if(c == KEY_RIGHT){
				if (trang < tongTrang){
					trang++;
						
					// Nap du lieu vao ban
					xoaDuLieuTrongBangVatTu();
					doDuLieuRaBangVatTu(dsVT, tongTrang, trang);	
					
					// Xoa con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			
			// CAP NHAT THONG TIN VAT TU
			} else if (c == KEY_INSERT){
				int vtVatTu = (trang - 1) * 10 + vtLuaChon - 1;
				suaVatTu(dsVT, dsVT.nodesVT[vtVatTu]);
												
				veKhungDanhSachVatTu();
				xoaDuLieuTrongBangVatTu();
				doDuLieuRaBangVatTu(dsVT, tongTrang, trang);	
	
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
						
			// XOA VAT TU	
			} else if (c == KEY_DELETE) {
				int vtVatTuXoa = (trang - 1) * 10 + vtLuaChon - 1;
				
				bool kqXoa = thongBaoXoaVatTu(dsVT, rootNV, dsVT.nodesVT[vtVatTuXoa].maVatTu);
				if (kqXoa) {
					tongTrang = tongSoTrangVatTu(dsVT);		
					if (trang > 1 && vtLuaChon == 1){
						trang--;
						vtLuaChon = SL_VAT_TU_TRONG_TRANG;
					} else if (vtLuaChon > 1) vtLuaChon--;
				}
				// ve form danh sach
				// Nap du lieu vao ban
				giaoDienVatTu(dsVT, rootNV);
				xoaDuLieuTrongBangVatTu();
				doDuLieuRaBangVatTu(dsVT, tongTrang, trang);	
					
				// Xoa con tro
				gotoxy(toaDoX , toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				// Gan vi tri moi cho con tro
				vtLuaChon = 1;	
				// Ve con tro
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
	
			} 
	
		} while (c != KEY_ESC);
	}
}
//int main(){
//	TreeNhanVien rootNV;
////	InitNhanVien(rootNV);
////	DocFile(rootNV);
//	DSVatTu dsVT;
//	dsVT.soLuongVatTu = 0;
//	loadFileVatTu(dsVT);
////	veKhungDanhSachVatTu();
////	doDuLieuRaBangVatTu(dsVT, 1, 1);
//	giaoDienVatTu(dsVT, rootNV);
////	veGiaoDienThemVatTu();
////	themMoiVatTu(dsVT);
//	return 0;
//}

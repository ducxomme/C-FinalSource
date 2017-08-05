#include "VatTu.cpp"

string tenCotBangCTHoaDon[6] = {"STT", "MA VAT TU", "SO LUONG", "DON GIA", "VAT", "THANH TIEN"};
string thuocTinhCTHoaDon[4] = {"Ma Vat Tu", "So Luong", "Don Gia", "VAT"};

int kiemTraRongCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	return (ctHoaDonFirst == NULL ? 1 : 0);
}

void InitCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	ctHoaDonFirst = NULL;
}

int tonTaiMaHoaDonTrongDSCtHD(PTR_CT_HoaDon &ctHDFirst, ChiTiet_HD ctHD){
	if(ctHDFirst == NULL)
		return 0;
	for(PTR_CT_HoaDon p = ctHDFirst; p != NULL; p = p->CT_HD_Next){
		if(p->chiTietHD.maVT == ctHD.maVT)
			return 1;
	}
	return 0;
}

PTR_CT_HoaDon getNodeCTHoaDon(ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = new Node_ChiTiet_HD;
	p->chiTietHD = ctHD;
	p->CT_HD_Next = NULL;
}

int insertCTHoaDonLast(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = getNodeCTHoaDon(ctHD);
	if(p == NULL)	return 0;
	PTR_CT_HoaDon q;
	if(ctHoaDonFirst == NULL){
		ctHoaDonFirst = p;
		return 1;
	}
	
	for(q = ctHoaDonFirst; q->CT_HD_Next != NULL; q=q->CT_HD_Next);
	q->CT_HD_Next = p;
	return 1;
}

int insertCTHoaDonFirst(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = getNodeCTHoaDon(ctHD);
	if(p == NULL)	return 0;
	if(ctHoaDonFirst == NULL){
		ctHoaDonFirst = p;
		return 1;
	}
	else{
		p->CT_HD_Next = ctHoaDonFirst;
		ctHoaDonFirst = p;
		return 1;
	}
}

int deleteFirstCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	if(kiemTraRongCTHoaDon(ctHoaDonFirst))	return 0;
	PTR_CT_HoaDon p = ctHoaDonFirst;
	ctHoaDonFirst = p->CT_HD_Next;
	delete p;
	return 1;
}

int deleteAfterCTHoaDon(PTR_CT_HoaDon p){
	if(p == NULL || p->CT_HD_Next == NULL)
		return 0;
	PTR_CT_HoaDon q = p->CT_HD_Next;
	p->CT_HD_Next = q->CT_HD_Next;
	delete q;
	return 1;
}

int deleteLast(PTR_CT_HoaDon &ctHDFirst){
	if(kiemTraRongCTHoaDon(ctHDFirst)) return 0;
	PTR_CT_HoaDon p = ctHDFirst;
	PTR_CT_HoaDon q;
	if(p->CT_HD_Next == NULL){
		ctHDFirst = NULL;	
		return 1;
	}
	for(p; p->CT_HD_Next != NULL; q=p, p=p->CT_HD_Next);
	return deleteAfterCTHoaDon(q);
}


PTR_CT_HoaDon timKiemCTHoaDonTheoViTri(PTR_CT_HoaDon &ctHDFirst, int viTri){
	int i = -1;
	PTR_CT_HoaDon p = ctHDFirst;
	while(p != NULL){
		i++;
		if(i == viTri) return p;
		p=p->CT_HD_Next;
	}
}


PTR_CT_HoaDon timViTriCoMaVT(PTR_CT_HoaDon ctHoaDonFirst, string maVT){
	if(ctHoaDonFirst == NULL)
		return NULL;
	for(PTR_CT_HoaDon p = ctHoaDonFirst; p != NULL; p=p->CT_HD_Next){
		if(p->chiTietHD.maVT == maVT)
			return p;
	}
	return NULL;
}

int deleteCTHoaDonTheoMaVT(PTR_CT_HoaDon &ctHoaDonFirst, string maVT){
	PTR_CT_HoaDon p = timViTriCoMaVT(ctHoaDonFirst, maVT);
	if(p == NULL)	return 0;
	PTR_CT_HoaDon q = ctHoaDonFirst;
	if(q == p)
	{
		deleteFirstCTHoaDon(ctHoaDonFirst);
		return 1;	
	}
	for(q; q->CT_HD_Next != NULL && q->CT_HD_Next != p; q=q->CT_HD_Next);
	deleteAfterCTHoaDon(q);
	return 1;
}

int demSoChiTietHD(PTR_CT_HoaDon ctHoaDonFirst){
	int dem = 0;
	for(PTR_CT_HoaDon p = ctHoaDonFirst; p != NULL; p=p->CT_HD_Next)
		dem++;
	return dem;
}

int soTrangChiTietHD(PTRHoaDon ptrHD){
	return demSoChiTietHD(ptrHD->hoaDon.CT_HD_First)/10 + (demSoChiTietHD(ptrHD->hoaDon.CT_HD_First) % 10 == 0 ? 0 : 1);
}

void duyetDanhSach(PTR_CT_HoaDon first){
	
	if(first == NULL){
		cout << "Danh sach hoa don rong" << endl;
		return;
	}
	PTR_CT_HoaDon p = first;
	while(p != NULL){
		cout << p->chiTietHD.maVT << "\t" << p->chiTietHD.soLuong << "\t" << p->chiTietHD.donGia << "\t" << p->chiTietHD.vat << endl;
		p = p->CT_HD_Next;
	}
	
}

string tenNVCuaHoaDon(TreeNhanVien &rootNV, string maHD){
	string tenNV = "";
	TreeNhanVien p = rootNV;
	if(p == NULL)	return tenNV;
	
	StackNV sp = NULL;
	do{
		while(p != NULL){
			push(sp, p);
			p=p->nvLeft;
		}
		if(sp != NULL){
			pop(sp, p);
			PTRHoaDon ptrHD = p->nhanVien.hoaDonFirst;
			while(ptrHD != NULL){
				if(ptrHD->hoaDon.soHoaDon == maHD)
					tenNV = p->nhanVien.ho + " " + p->nhanVien.ten;
				ptrHD = ptrHD->HD_Next;
			}
			p=p->nvRight;
		}else return tenNV;		
	}while (1);
	
}

void capNhapSoLuongTonKho(DSVatTu &dsVT, char loai, ChiTiet_HD ctHD){
	for(int i = 0; i < dsVT.soLuongVatTu; i++){
		if(dsVT.nodesVT[i].maVatTu == ctHD.maVT){
			if(loai == 'N'){
				dsVT.nodesVT[i].soLuongTon += ctHD.soLuong;
				return;
			}else{
				dsVT.nodesVT[i].soLuongTon -= ctHD.soLuong;
				return;
			}
		}
	}
}

void congDonSoLuongNeuTrungMa(PTR_CT_HoaDon &ctHDFirst, ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = ctHDFirst;
	for(p; p != NULL; p = p->CT_HD_Next){
		if(p->chiTietHD.maVT == ctHD.maVT){
			p->chiTietHD.soLuong += ctHD.soLuong;
			return;
		}
	}
}

long long tinhTongTienMotVatTu(ChiTiet_HD ctHD){
	long long tong = 0;
	tong = (ctHD.donGia * ctHD.soLuong);
	
	return tong * double((100 + ctHD.vat)/ 100.0);
}

long long tinhTongGiaTriHoaDon(PTR_CT_HoaDon ctHDFirst){
	long long tong = 0;
	PTR_CT_HoaDon p = ctHDFirst;
	if(p == NULL) return 0;
	while(p != NULL){
		tong += tinhTongTienMotVatTu(p->chiTietHD);
		p = p->CT_HD_Next;
	}
	return tong;
}

void veGiaoDienThemCTHoaDon(){
	Normal();
	system("cls");
		
	veHinhChuNhat(45, 4, 30, 3, RED);
	SetBGColor(4);
	gotoxy(49, 5);
	cout << "NHAP CHI TIET HOA DON";
	Normal();

	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < 4; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		SetColor(YELLOW);
		cout << thuocTinhCTHoaDon[i];
		
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}

	Normal();	
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}

	gotoxy(28, 25);
	cout << "ESC: Tro ve \t F2: Luu \t F5: DS Vat Tu Da Nhap   INSERT: DS Vat Tu";	
}

void themMotChiTietHoaDon(DSVatTu &dsVT, HoaDon &hd){
NHAPCTHOADON:
	veGiaoDienThemCTHoaDon();
	
	ChiTiet_HD ctHD;
	string donGia = "";
	string vat = "";
	string soLuong = "";
	
	string errors[4] = {"", "", "", ""};
	int c;
	bool res;
	int soLuongXuat;
	// vi tri xuat cac ma vat tu da nhap
	int XViTri = 89;
	int YViTri = 3;
		
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInput = 41;
	int toaDoYInput = 9;
	
	int viTriNhapLieu = 0;
	do{
		switch(viTriNhapLieu){
			case 0:
				c = nhapChuoiKiTuVaSo(ctHD.maVT, toaDoXInput, toaDoYInput , WIDTH_INPUT_TEXT, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(ctHD.maVT.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu]; 
				
				}else if(timViTriVatTuTrung(dsVT, chuyenChuoiThanhChuoiHoa(ctHD.maVT)) == -1){
					errors[viTriNhapLieu] = "Vat Tu khong ton tai";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else errors[viTriNhapLieu] = "";
				
				break;
			case 1:	
				c = nhapChuoiKiTuSo(soLuong, toaDoXInput, toaDoYInput + viTriNhapLieu * 3, 10 , BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				stringstream(soLuong) >> soLuongXuat;
				if(hd.loai == 'X'){
					if (soLuong.length() <= 0) {	
						errors[viTriNhapLieu] = "Khong duoc de trong!";
						SetColor(TEXT_ERROR);
						gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
						cout << errors[viTriNhapLieu];
					}
					else if(soLuongXuat > soLuongVatTuTonKhoCuaMaVT(dsVT, chuyenChuoiThanhChuoiHoa(ctHD.maVT))){
						errors[viTriNhapLieu] = "SL ton cua " + ctHD.maVT + " : " + to_string(soLuongVatTuTonKhoCuaMaVT(dsVT, chuyenChuoiThanhChuoiHoa(ctHD.maVT)));
						SetColor(TEXT_ERROR);
						gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
						cout << errors[viTriNhapLieu];
					}
					else errors[viTriNhapLieu] = "";
				}
				else{
					if (soLuong.length() <= 0) {	
						errors[viTriNhapLieu] = "Khong duoc de trong!";
						SetColor(TEXT_ERROR);
						gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
						cout << errors[viTriNhapLieu];

					}else errors[viTriNhapLieu] = "";
				}
				break;
			case 2:	
				c = nhapChuoiKiTuSo(donGia, toaDoXInput , toaDoYInput + viTriNhapLieu * 3, 20, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if (donGia.length() <= 0) {
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
				
				break;
			case 3:	
				c = nhapChuoiKiTuSo(vat, toaDoXInput , toaDoYInput + viTriNhapLieu * 3, 2, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if (vat.length() <= 0) {
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
				
				break;
		}
		
		if((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < 3) viTriNhapLieu++;
		
		if(c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F2){
			if(ctHD.maVT.length() > 0 && soLuong.length() > 0 && donGia.length() > 0 && vat.length() > 0){
				if(timViTriVatTuTrung(dsVT, chuyenChuoiThanhChuoiHoa(ctHD.maVT)) != -1){
					if(hd.loai == 'X'){
						if (soLuongXuat <= soLuongVatTuTonKhoCuaMaVT(dsVT, chuyenChuoiThanhChuoiHoa(ctHD.maVT))){
							ctHD.maVT = chuyenChuoiThanhChuoiHoa(ctHD.maVT);
							stringstream(soLuong) >> ctHD.soLuong;
							stringstream(donGia) >> ctHD.donGia;
							stringstream(vat) >> ctHD.vat;
							if(tonTaiMaHoaDonTrongDSCtHD(hd.CT_HD_First, ctHD)){
								congDonSoLuongNeuTrungMa(hd.CT_HD_First, ctHD);
								thongBao("Them vat tu thanh cong!!", 45, 12, 27, 3);
							}
							else {
								res = insertCTHoaDonLast(hd.CT_HD_First, ctHD);	
								if(res == true){
									thongBao("Them vat tu thanh cong!!", 45, 12, 27, 3);
								}else
									thongBao("That bai", 45, 12, 27, 3);
							}
							capNhapSoLuongTonKho(dsVT, hd.loai, ctHD);
							goto NHAPCTHOADON;
						}
					}
					else {
						ctHD.maVT = chuyenChuoiThanhChuoiHoa(ctHD.maVT);
						stringstream(soLuong) >> ctHD.soLuong;
						stringstream(donGia) >> ctHD.donGia;
						stringstream(vat) >> ctHD.vat;
						if(tonTaiMaHoaDonTrongDSCtHD(hd.CT_HD_First, ctHD)){
							congDonSoLuongNeuTrungMa(hd.CT_HD_First, ctHD);
							thongBao("Them vat tu thanh cong!!", 45, 12, 27, 3);
						}
						else {
							res = insertCTHoaDonLast(hd.CT_HD_First, ctHD);	
							if(res == true){
								thongBao("Them vat tu thanh cong!!", 45, 12, 27, 3);
							}else
								thongBao("That bai", 45, 12, 27, 3);
						}
						capNhapSoLuongTonKho(dsVT, hd.loai, ctHD);
						goto NHAPCTHOADON;						
					}
				}
			}
		}
		
		// Xoa Chi Tiet HOa Don vua nhap
		if(c == KEY_DELETE){
			if(hd.CT_HD_First == NULL){
				thongBao("Chua co CTHD nao!", 45, 12, 27, 3);
			}else{
				res = deleteLast(hd.CT_HD_First);
				if(res == 1){
					thongBao("Xoa thanh cong", 45, 20, 27, 3);
				}else{
					thongBao("That bai", 45, 20, 27, 3);
				}
			}
			goto NHAPCTHOADON;
			
		}
		
		if(c == KEY_F5){
			if(hd.CT_HD_First == NULL){
				thongBao("Chua co vat tu nao!", 45, 20, 27, 3);
				goto NHAPCTHOADON;
			}else{
				giaoDienCacVatTuDaNhap(hd.CT_HD_First);
				goto NHAPCTHOADON;
			}
		}
		
		
		if(c== KEY_INSERT){
			xemDanhSachVatTu(dsVT);
			goto NHAPCTHOADON;		
		}
		
		if(c == KEY_ESC){
			system("cls");
			break;
		}
		
	}while (c != KEY_ESC);
	
}

void veKhungChiTietHoaDonDaLap(TreeNhanVien &rootNV, PTRHoaDon ptrHD){
	Normal();
	system("cls");
	gotoxy(2, 0);	cout << "Nhan Vien: " << tenNVCuaHoaDon(rootNV, ptrHD->hoaDon.soHoaDon);
	gotoxy(2, 1);	cout << "So HD: " << ptrHD->hoaDon.soHoaDon;
	gotoxy(2, 2); 	cout << "Loai: " << (ptrHD->hoaDon.loai == 'N' ? "Nhap" : "Xuat");
	gotoxy(2, 3);	cout << "Ngay lap: " << chuyenNgayThanhChuoi(ptrHD->hoaDon.ngayLapHoaDon); 
	// In tieu de
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "CHI TIET HOA DON";
	Normal();
	veBangDanhSach(4, 4, 1, 10, 4);
	veKhungDanhSach(5, 10, 9, 4);
	veLaiGoc(4, 4, 10);
	
	//veChuThich();
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(78, 25); cout << "TONG TIEN : ";
	gotoxy(32, 28);
	cout << "ESC: Thoat       <-Trang truoc \t Trang sau->";
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 6; i++){
		if(i == 0){
			toaDoXNhan = 6;
		}
		else toaDoXNhan =  10 + (TABLE_COLUMN_WIDTH - tenCotBangCTHoaDon[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangCTHoaDon[i];
	}
	Normal();	
}

void veKhungCTHDDaLap(PTR_CT_HoaDon &ctHDFirst){
	Normal();
	system("cls");	
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DS VAT TU VUA NHAP";
	Normal();
	veBangDanhSach(14, 4, 1, 10, 4);
	veKhungDanhSach(4, 10, 19, 4);
	veLaiGoc(14, 4, 10);
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(32, 28);
	cout << "ESC: Thoat \t DELETE: Xoa      <-Trang truoc \t Trang sau->";
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 5; i++){
		if(i == 0){
			toaDoXNhan = 16;
		}
		else toaDoXNhan =  19 + (20 - tenCotBangCTHoaDon[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangCTHoaDon[i];
	}
	Normal();
}

void xoaDuLieuTrongDSVatTuVuaNhap(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	int j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(16, j);
		cout << "   ";
		j += 2;
	}
	
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(20, j);
		cout << "                    ";
		j += 2;
	}
	
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(41, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(62, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(83, j);
		cout << "                    ";
		j += 2;
	}	
}

void xoaDuLieuTrongKhungCTHD(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	int j = 7;
	
	for(int i = 0; i < 9; i++){
		gotoxy(6, j);
		cout << "   ";
		j += 2;
	}
	
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(10, j);
		cout << "                    ";
		j += 2;
	}
	
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(31, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(52, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(73, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 9; i++){
		gotoxy(94, j);
		cout << "                    ";
		j += 2;
	}
	
}

void doDuLieuRaBangChiTietHoaDon(PTRHoaDon ptrHD, int tongTrang, int trang){
	xoaDuLieuTrongKhungCTHD();
	
	PTR_CT_HoaDon p = ptrHD->hoaDon.CT_HD_First;
	
	int soCTHD = demSoChiTietHD(ptrHD->hoaDon.CT_HD_First);
	
	int vtDau = (trang - 1) * 9;
	int dem = 0;
	while(p != NULL && dem < vtDau){
		p = p->CT_HD_Next;
		dem++;
	}

	int j = 7;
	string str = "";
	for(int i = vtDau; i < trang * 9 && i < soCTHD; i++){
		gotoxy(6 , j);
		str = chuyenSoThanhChuoi(i + 1);
		cout << str;
		j += 2;
	}
	while(p != NULL && vtDau < trang * 9){
		gotoxy(10,  7 + (vtDau % 9) * 2);
		cout << p->chiTietHD.maVT;
		
		gotoxy(31, 7 + (vtDau % 9) * 2);
		cout << p->chiTietHD.soLuong;
		
		gotoxy(52, 7 + (vtDau % 9) * 2);
		cout << p->chiTietHD.donGia;

		gotoxy(73, 7 + (vtDau % 9) * 2);
		cout << p->chiTietHD.vat;
		
		// Tinh gia tri don hang
		gotoxy(94, 7 + (vtDau % 9) * 2);
		cout << tinhTongTienMotVatTu(p->chiTietHD);
		
		vtDau++;
		p = p->CT_HD_Next;
	}
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(81,2);
	cout << page;	
}

void xuatCacVatTuDaNhap(PTR_CT_HoaDon &ptrCTHD, int tongTrang, int trang){
	PTR_CT_HoaDon p = ptrCTHD;
	string str;
	int soCTHD = demSoChiTietHD(ptrCTHD);
	
	int vtDau = (trang - 1) * 10;
	
	int j = 7;
	for(int i = vtDau; i < trang * 9 && i < soCTHD; i++){
		gotoxy(16 , j);
		str = chuyenSoThanhChuoi(i + 1);
		cout << str;
		j += 2;
	}
	
	while(p != NULL && vtDau < trang * 10){
		gotoxy(19 + (20 - p->chiTietHD.maVT.length()) / 2,  7 + (vtDau % 10) * 2);
		cout << p->chiTietHD.maVT;
		
		gotoxy(40 + (20 - chuyenSoThanhChuoi(p->chiTietHD.soLuong).length()) / 2, 7 + (vtDau % 10) * 2);
		cout << p->chiTietHD.soLuong;
		
		gotoxy(61 + (20 - chuyenSoThanhChuoi(p->chiTietHD.donGia).length()) / 2, 7 + (vtDau % 10) * 2);
		cout << p->chiTietHD.donGia;

		gotoxy(82 + (20 - chuyenSoThanhChuoi(p->chiTietHD.vat).length()) / 2, 7 + (vtDau % 10) * 2);
		cout << p->chiTietHD.vat;
		
		vtDau++;
		p = p->CT_HD_Next;
	}
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);
	gotoxy(88, 3); cout << page;		
}

void giaoDienCacVatTuDaNhap(PTR_CT_HoaDon &ptrCTHD){
	int trang = 1;
	int soLuongCTHD = demSoChiTietHD(ptrCTHD);
	int tongTrang = soLuongCTHD/10 + (soLuongCTHD % 10 == 0 ? 0 : 1);
	if(soLuongCTHD == 0) tongTrang = 1;
	int c;
	int vtLuaChon = 1;
	int toaDoX = 11;
	int toaDoY = 7;
	veKhungCTHDDaLap(ptrCTHD);
	xuatCacVatTuDaNhap(ptrCTHD, tongTrang, trang);
	gotoxy(toaDoX, toaDoY);
	cout << "->";
	do{
		c = keyPressed();
		if(c == KEY_UP){
			if(vtLuaChon > 1){
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				vtLuaChon--;
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
			}
		}else if(c == KEY_DOWN){
				
				if(vtLuaChon < 10 && (vtLuaChon + (trang - 1) * 9) < soLuongCTHD){
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					vtLuaChon++;
					
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				}
		}else if(c == KEY_LEFT){
				if(trang > 1) trang--;
				
				xoaDuLieuTrongDSVatTuVuaNhap();
				xuatCacVatTuDaNhap(ptrCTHD, tongTrang, trang);
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";
				
		}else if(c == KEY_RIGHT){
				if(trang < tongTrang) trang++;
				
				xoaDuLieuTrongDSVatTuVuaNhap();
				xuatCacVatTuDaNhap(ptrCTHD, tongTrang, trang);
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";		
		}else if(c == KEY_DELETE){
			int vtCTHD = (trang - 1) * 10 + vtLuaChon - 1;
			PTR_CT_HoaDon p = timKiemCTHoaDonTheoViTri(ptrCTHD, vtCTHD);
			if(p != NULL){
				string mess = "Ban co muon xoa " + p->chiTietHD.maVT + " khong ?(Y/N) :";
				int xacNhanXoa = hopThoaiLuaChon(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5)/2, mess.length() + 10, 4 );
				if(xacNhanXoa == 1){
					if(deleteCTHoaDonTheoMaVT(ptrCTHD, p->chiTietHD.maVT)){
						thongBao("Xoa thanh cong", 45, 20, 27, 3);
						
						soLuongCTHD = demSoChiTietHD(ptrCTHD);
						tongTrang = soLuongCTHD/10 + (soLuongCTHD % 10 == 0 ? 0 : 1);
						if(soLuongCTHD == 0) tongTrang = 1;
						if (trang > 1 && vtLuaChon == 1){
							trang--;
							vtLuaChon = 10;
						
						}else if (vtLuaChon > 1) vtLuaChon--;
					}else	thongBao("That bai", 45, 20, 27, 3);				
				}
				
			}
			veKhungCTHDDaLap(ptrCTHD);
			xoaDuLieuTrongDSVatTuVuaNhap();
			xuatCacVatTuDaNhap(ptrCTHD, tongTrang, trang);

			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "->";				
			}
			
	}while(c != KEY_ESC);	
}

void giaoDienChiTietHoaDon(TreeNhanVien &rootNV, DSVatTu &dsVT, PTRHoaDon ptrHD){
	
ABCXYZ:
	int trang = 1;
	int tongTrang = soTrangChiTietHD(ptrHD);
	if(tongTrang == 0) tongTrang = 1;
	int vtLuaChon = 1;
	int c;
	int soLuongCTHD = demSoChiTietHD(ptrHD->hoaDon.CT_HD_First);
	
	
	veKhungChiTietHoaDonDaLap(rootNV, ptrHD);
	doDuLieuRaBangChiTietHoaDon(ptrHD, tongTrang, trang);
	gotoxy(94, 25);
	cout << tinhTongGiaTriHoaDon(ptrHD->hoaDon.CT_HD_First);
	
	if(ptrHD->hoaDon.CT_HD_First == NULL){
		gotoxy(32, 28);
		cout << "ESC: Thoat       <-Trang truoc \t Trang sau->     INSERT: Nhap CTHD";
	}
	
	do{
		if(ptrHD->hoaDon.CT_HD_First == NULL){
			c = keyPressed();
			if(c == KEY_INSERT){
				themMotChiTietHoaDon(dsVT, ptrHD->hoaDon);
				goto ABCXYZ;
			}
			if(c == KEY_ESC){
				break;
			}
		}
		c = keyPressed();
		if(c == KEY_LEFT){
				if(trang > 1) trang--;
				
				xoaDuLieuTrongKhungCTHD();
				doDuLieuRaBangChiTietHoaDon(ptrHD, tongTrang, trang);
				
				gotoxy(94, 25);
				cout << tinhTongGiaTriHoaDon(ptrHD->hoaDon.CT_HD_First);
				
		}else if(c == KEY_RIGHT){
				if(trang < tongTrang) trang++;
				
				xoaDuLieuTrongKhungCTHD();
				doDuLieuRaBangChiTietHoaDon(ptrHD, tongTrang, trang);
				gotoxy(94, 25);
				cout << tinhTongGiaTriHoaDon(ptrHD->hoaDon.CT_HD_First);
	
		}

	}while(c != KEY_ESC);
}	



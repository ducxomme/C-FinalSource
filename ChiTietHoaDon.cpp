#include "VatTu.cpp"

string tenCotBangCTHoaDon[5] = {"STT", "MA VAT TU", "SO LUONG", "DON GIA", "VAT"};
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
		Normal();
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}

	gotoxy(32, 25);
	cout << "ESC: Tro ve \t F2: Luu \t DELETE: Xoa Vat Tu vua nhap";	
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
						if (soLuongXuat <= soLuongVatTuTonKhoCuaMaVT(dsVT, ctHD.maVT)){
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
		
	}while (c != KEY_ESC);
	
}
//
//int main(){
//	
//	PTR_CT_HoaDon ctHoaDonFirst;
//	InitCTHoaDon(ctHoaDonFirst);
//	
//	ChiTiet_HD cthd1;
//	cthd1.maVT = "VT1";
//	cthd1.soLuong = 100;
//	cthd1.donGia = 200000;
//	cthd1.vat = 0.1;
//	insertCTHoaDonLast(ctHoaDonFirst, cthd1);
//
//	ChiTiet_HD cthd2;
//	cthd2.maVT = "VT2";
//	cthd2.soLuong = 400;
//	cthd2.donGia = 100000;
//	cthd2.vat = 0.1;
//	insertCTHoaDonLast(ctHoaDonFirst, cthd2);
//	
//	ChiTiet_HD cthd3;
//	cthd3.maVT = "VT3";
//	cthd3.soLuong = 300;
//	cthd3.donGia = 300000;
//	cthd3.vat = 0.1;
//	insertCTHoaDonLast(ctHoaDonFirst, cthd3);
//	
//	ChiTiet_HD cthd4;
//	cthd4.maVT = "VT4";
//	cthd4.soLuong = 200;
//	cthd4.donGia = 400000;
//	cthd4.vat = 0.1;
//	insertCTHoaDonLast(ctHoaDonFirst, cthd4);
//	
//	ChiTiet_HD cthd5;
//	cthd5.maVT = "VT5";
//	cthd5.soLuong = 100;
//	cthd5.donGia = 500000;
//	cthd5.vat = 0.1;
//	insertCTHoaDonLast(ctHoaDonFirst, cthd5);
//	
//	deleteCTHoaDonTheoMaVT(ctHoaDonFirst, "VT8");
//	duyetDanhSach(ctHoaDonFirst);
//	DSVatTu dsVT;
//	dsVT.soLuongVatTu = 0;
//	HoaDon hd;
//
//	themMotChiTietHoaDon(dsVT, hd);
	
//	return 0;
//}

#include "HoaDon.cpp"

string tenThuocTinhNhanVien[] = {"Ma Nhan Vien", "Ho Nhan Vien", "Ten Nhan Vien", "Phai(1: NAM; 0: NU)"};
string tenCotBangNhanVien[] = {"STT", "MA NHAN VIEN", "HO NHAN VIEN", "TEN NHAN VIEN", "PHAI"};


int EmptyTreeNV(TreeNhanVien &rootNV){
	return (rootNV == NULL ? 1 : 0);
}

void InitNhanVien(TreeNhanVien &rootNV){
	rootNV = NULL;
}

TreeNhanVien getNodeNhanVien(NhanVien nv){
	TreeNhanVien treeNV = new NodeNhanVien;
	treeNV->nhanVien = nv;
	treeNV->nvLeft = NULL;
	treeNV->nvRight = NULL;
	
	return treeNV;
}

bool Insert_Node(TreeNhanVien &rootNV, NhanVien nv){
	if(rootNV == NULL){
		rootNV = getNodeNhanVien(nv);
		return true;
	}else{
		if(nv.maNhanVien < rootNV->nhanVien.maNhanVien)
			Insert_Node(rootNV->nvLeft, nv);
		else if(nv.maNhanVien > rootNV->nhanVien.maNhanVien)
			Insert_Node(rootNV->nvRight, nv);
		else return false;
	}

}
//TreeNhanVien rp;
void timNodeNVTheMang(TreeNhanVien &nodeNVRight){ //Tim node trai nhat cua node NV ben phai
	TreeNhanVien rp;
	if(nodeNVRight->nvLeft != NULL)
		timNodeNVTheMang(nodeNVRight->nvLeft);
	else{
		rp->nhanVien = nodeNVRight->nhanVien;
		rp = nodeNVRight;
		nodeNVRight = rp->nvRight;		
	}
}

void xoaNodeNhanVien(TreeNhanVien &rootNV, string maNV){
	TreeNhanVien rp;
	if(rootNV == NULL)	return;
	else{
		if(rootNV->nhanVien.maNhanVien > maNV)
			xoaNodeNhanVien(rootNV->nvLeft, maNV);
		else if(rootNV->nhanVien.maNhanVien < maNV)
			xoaNodeNhanVien(rootNV->nvRight, maNV);
		else{
			rp = rootNV;
			if(rp->nvRight == NULL)
				rootNV = rp->nvLeft;                                                                  
			else if(rp->nvLeft == NULL)
				rootNV = rp->nvRight;
			else
				timNodeNVTheMang(rp->nvRight);
			delete rp;
		}
	}
}

TreeNhanVien search_NhanVien(TreeNhanVien &rootNV, string maNV){
	TreeNhanVien p;
	p = rootNV;
	while(p != NULL && p->nhanVien.maNhanVien != maNV){
		if(maNV < p->nhanVien.maNhanVien)
			p=p->nvLeft;
		else p = p->nvRight;
	}
	return p;
}

TreeNhanVien timKiemNhanVienTheoViTri(TreeNhanVien & rootNV, int viTri){
	TreeNhanVien p = rootNV;
	StackNV sp = NULL;
	int dem = 0;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->nvLeft;
		}
		if(sp != NULL && dem < viTri+1){
			pop(sp, p);
			dem++;
			if(dem - 1 == viTri) return p;
			p=p->nvRight;
		}
		else break;
	}while(1);
}

void testLNR_MA_NhanVien(TreeNhanVien &rootNV){
	StackNV sp = NULL;
	TreeNhanVien p = rootNV;
	do{
		while(p != NULL){
			push(sp, p);
			p=p->nvLeft;
		}
		
		if(sp != NULL){
			pop(sp, p);
			cout << p->nhanVien.maNhanVien << endl;
			p=p->nvRight;
		}
		else break;
	}while(1);
	
}

void testInorder(TreeNhanVien &rootNV){
	if(rootNV != NULL){
		testInorder(rootNV->nvLeft);
		cout << rootNV->nhanVien.maNhanVien << endl;
		testInorder(rootNV->nvRight);
	}
}

int demSoNhanVien(TreeNhanVien &rootNV){
	StackNV sp = NULL;
	int dem = 0;
	TreeNhanVien p = rootNV;
	while(p != NULL){
		dem++;
		if(p->nvRight != NULL)
			push(sp, p->nvRight);
		if(p->nvLeft != NULL)
			p = p->nvLeft;
		else if(sp == NULL)
			break;
		else pop(sp, p);
	}
	return dem;
}

int tongSoTrangNhanVien(TreeNhanVien &rootNV){
	int tongNhanVien = demSoNhanVien(rootNV);
	return (tongNhanVien / 10) + (tongNhanVien % 10 == 0 ? 0 : 1);
}

void initStackNhanVien(StackNV &sp){
	sp = NULL;
}

void veGiaoDienThemNhanVien(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	system("cls");
	Normal();
	veHinhChuNhat(45, 4, 26, 3, RED);
	SetBGColor(RED);
	gotoxy(52, 5);
	cout << "THEM NHAN VIEN";
	Normal();
	
	for(int i = 0; i < 4; i++){
		gotoxy(25, 9 + 3 * i);
		SetColor(YELLOW);
		cout << tenThuocTinhNhanVien[i];
		Normal();
		if(i == 3)
			veBangDanhSach(45, 17, 1, 1, 3);
		else veInputText(45, 8 + 3 * i);
	}
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(46, 25);
	cout << "ESC: Tro ve \t F2: Luu";
}

void themMotNhanVien(TreeNhanVien &rootNV){
THEMNHANVIEN:	
	veGiaoDienThemNhanVien();
	NhanVien nv;
	int c;
	string errors[4] = {"", "", "", ""};
	string phai;
	bool res;
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInput = 46;
	int toaDoYInput = 9;
	
	
	int viTriNhapLieu = 0;
	do{
		switch(viTriNhapLieu){
			case 0:
				c = nhapChuoiKiTuVaSo(nv.maNhanVien, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, WIDTH_INPUT_TEXT, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(nv.maNhanVien.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(search_NhanVien(rootNV, chuyenChuoiThanhChuoiHoa(nv.maNhanVien)) != NULL){
					errors[viTriNhapLieu] = chuyenChuoiThanhChuoiHoa(nv.maNhanVien) + " da trung !";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(kiemTraChuoiCoKhoangTrang(nv.maNhanVien)){
					errors[viTriNhapLieu] = "Khong duoc co ky tu khoang trang!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else
					errors[viTriNhapLieu] = "";
				
				break;
			
			case 1:
				c = nhapChuoiKiTuVaSo(nv.ho, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, WIDTH_INPUT_TEXT, BLACK, WHITE);

				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(nv.ho.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(!kiemTraChuoiNhapVao(nv.ho)){
					errors[viTriNhapLieu] = "Ho khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else
					errors[viTriNhapLieu] = "";
				break;	
				
			case 2:
				c = nhapChuoiKiTuVaSo(nv.ten, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, WIDTH_INPUT_TEXT, BLACK, WHITE);

				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(nv.ten.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(!kiemTraChuoiNhapVao(nv.ten)){
					errors[viTriNhapLieu] = "Ten khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else
					errors[viTriNhapLieu] = "";
				
				break;
			case 3:
				c = nhapKyTu(phai, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, 1, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(phai.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				
				}else if(!kiemTraChuoiNhapVao(phai)){
					errors[viTriNhapLieu] = "Khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				}else
					errors[viTriNhapLieu] = "";
				
				break;	
		}
		
		if ((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < 3) viTriNhapLieu++;
		
		if (c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F2){
			if (nv.maNhanVien.length() > 0 && nv.ho.length() > 0 && nv.ten.length() > 0 && phai.length() > 0) {
				nv.maNhanVien = chuyenChuoiThanhChuoiHoa(nv.maNhanVien);
				nv.ho = dinhDangChuoiNhapVao(nv.ho);
				nv.ten = dinhDangChuoiNhapVao(nv.ten);
				nv.phai = (phai == "1" ? true : false);
				nv.hoaDonFirst = NULL;
				res = Insert_Node(rootNV, nv);
				if(res == true){
					thongBao("Them thanh cong!!", 45, 12, 27, 3);
				
				}else{
					thongBao("That bai!!", 45, 12, 27, 3);
				}
				
				goto THEMNHANVIEN;
			}	
		}
		if(c == KEY_ESC) {
			system("cls");
			break;
		}	
	}while(1);
}

void veKhungDanhSachNhanVien(){
	Normal();
	system("cls");
	// In tieu de
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DANH SACH NHAN VIEN";
	veBangDanhSach(13, 4, 1, 11, 4);
	veKhungDanhSach(4, 11, 18, 4);
	veLaiGoc(13, 4, 11);
	
	//veChuThich();
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(9, 28);
	cout << "ESC: Thoat   \tF5: DS Hoa Don  \t INSERT: Hieu chinh \t DELETE: Xoa \t <-Trang truoc \t Trang sau->";
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 5; i++){
		if(i == 0){
			toaDoXNhan = 15;
		}
		else toaDoXNhan =  19 + (TABLE_COLUMN_WIDTH - tenCotBangNhanVien[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangNhanVien[i];
	}
	Normal();
}

void xoaDuLieuTrongBangNhanVien(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	int j = 7;
	// XOA stt
	for(int i = 0; i < 10; i++){
		gotoxy(14, j);
		cout << "    ";
		j += 2;
	}
	// Xoa MA NV
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(19, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa ho NV
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(40, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa ten
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(82, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa Phai
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(61, j);
		cout << "                    ";
		j += 2;
	}
}

void doDuLieuRaBangNhanVien(TreeNhanVien &rootNV, int tongTrang, int trang){
	xoaDuLieuTrongBangNhanVien();
	StackNV sp = NULL;
	TreeNhanVien p = rootNV;
	int soNhanVien = demSoNhanVien(rootNV);
	int dem = 0;
	// Ghi du lieu moi vao bang
	SetColor(WHITE);	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;	
	int vtDau = (trang - 1) * 10;	
	string str;
	int hang = 7;
	// STT
	for(int i = vtDau; i < trang * 10 && i < soNhanVien; i++){
		gotoxy(15, hang);
		str = chuyenSoThanhChuoi(i + 1);
		cout << str;
		hang += 2;
	}
	do{
		while(p != NULL){
			push(sp, p);
			p = p->nvLeft;
		}
		
		if(sp != NULL){
			pop(sp, p);
			if(dem >= (trang - 1) * SO_DONG_MOT_TRANG && dem < trang * SO_DONG_MOT_TRANG){
					
				gotoxy(19 + 0 * 21 + (20 - p->nhanVien.maNhanVien.length())/2, 7+ (dem % 10) * 2);
				SetBGColor(BLACK);
				SetColor(WHITE);
				cout << p->nhanVien.maNhanVien;
					
				gotoxy(18 + 1 * 21 + (20 - p->nhanVien.ho.length())/2, 7+ (dem % 10) * 2);
				SetBGColor(BLACK);
				SetColor(WHITE);
				cout << p->nhanVien.ho;
					
				gotoxy(18 + 2 * 21 + (20 - p->nhanVien.ten.length())/2, 7 + (dem % 10) * 2);
				SetBGColor(BLACK);
				SetColor(WHITE);
				cout << p->nhanVien.ten;
					
				gotoxy(18 + 3 * 21 + (20 - 3)/2,  7 + (dem % 10) * 2);
				SetBGColor(BLACK);
				SetColor(WHITE);
				if(p->nhanVien.phai == true) cout << "Nam";
				else cout << "Nu";
			}
				
			dem++;
			p = p->nvRight;
		}else break;
		
	}while(true);
	
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(81,2);
	cout << page;
}

void suaNhanVien(NhanVien &nv){
	system("cls");
	int c;
	string phai;
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInputText = 46;
	int toaDoYInputText = toaDoYNhan;

	veGiaoDienThemNhanVien();
	
	SetColor(YELLOW);
	gotoxy(46, 9);
	cout << nv.maNhanVien;

	
	SetColor(WHITE);
	gotoxy(46, 12);
	cout << nv.ho;
	gotoxy(46, 15);
	cout << nv.ten;
	gotoxy(46, 18);
	if(nv.phai = true)
		phai = "1";
	else phai = "0";
	cout << phai;
	
	string errors[4] = {"", "", "", ""};
	int viTriNhapLieu = 1;
	
	do {
		switch (viTriNhapLieu){
							
			// Nhap hoNV
			case 1:	
				c = nhapChuoiKiTuVaSo(nv.ho, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
					// Kiem tra rong
				if (nv.ho.length() <= 0) {	
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
					
				break;
				
			// Nhap tenNV
			case 2:	
				c = nhapChuoiKiTuVaSo(nv.ten, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BLACK, WHITE);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
				if (nv.ten.length() <= 0) {
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
				
				break;
			
			//Nhap phai	
			case 3:
				c = nhapKyTu(phai, toaDoXInputText, toaDoYInputText + 3 * viTriNhapLieu, 1, BLACK, WHITE);
				
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(phai.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				
				}else if(!kiemTraChuoiNhapVao(phai)){
					errors[viTriNhapLieu] = "Khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				}else
					errors[viTriNhapLieu] = "";
				break;	
			
		}
		
		if ((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < 3) viTriNhapLieu++;
		
		if (c == KEY_UP && viTriNhapLieu > 1) viTriNhapLieu--;
		
		if(c == KEY_F2){
			if (nv.ho.length() > 0 && nv.ten.length() > 0 && phai.length() > 0){
				
				nv.ho = dinhDangChuoiNhapVao(nv.ho);
				nv.ten = dinhDangChuoiNhapVao(nv.ten);
				nv.phai = (phai == "1" ? true : false);
		
				string noiDungThongBao = "Cap nhat thanh cong: ";
				thongBao(noiDungThongBao, 24 + (86 - noiDungThongBao.length()) / 2, 5 + 7, noiDungThongBao.length() + 10, 5);
				break;
			}
		}
	} while (c != KEY_ESC);	
		
}

void giaoDienNhanVien(TreeNhanVien &rootNV, DSVatTu &dsVT){
	if(EmptyTreeNV(rootNV)){
		string noiDungThongBao = "Danh sach Vat Tu rong!";
		thongBao(noiDungThongBao, 43, 2, noiDungThongBao.length() + 10, 3);			
	}else{
		int trang = 1;
		int tongTrang = tongSoTrangNhanVien(rootNV);
		int vtLuaChon = 1;
		int c;
		string s;
		int dem = demSoNhanVien(rootNV);
		int soCot = 5;
		int soDong = 10 ;
		int toaDoX = 10;
		int toaDoY = 7;
		
		veKhungDanhSachNhanVien();
		doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);	
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
				if (vtLuaChon < 10 && (vtLuaChon + (trang - 1) * 10) < dem) 
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
					veKhungDanhSachNhanVien();
					doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);	
					
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
					veKhungDanhSachNhanVien();
					doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);	
					
					// Xoa con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			
			// CAP NHAT THONG TIN NHAN VIEN
			} else if (c == KEY_INSERT){
				int vtNhanVien = (trang - 1) * 10 + vtLuaChon - 1;
				suaNhanVien(timKiemNhanVienTheoViTri(rootNV, vtNhanVien)->nhanVien);
												
				veKhungDanhSachNhanVien();
				xoaDuLieuTrongBangNhanVien();
				doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);	
	
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
						
			// XOA NV
			} else if (c == KEY_DELETE) {
				int vtNhanVien = (trang - 1) * 10 + vtLuaChon - 1;
				
				TreeNhanVien p = timKiemNhanVienTheoViTri(rootNV, vtNhanVien);
				if(p != NULL){
					if(p->nhanVien.hoaDonFirst != NULL){
						string mess = "Khong duoc phep xoa";
						thongBao(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, mess.length() + 10, 5);
						break;
					}else{
						
						string mess = "Ban co muon xoa " + p->nhanVien.maNhanVien + " khong?(y/n): ";
						int xacNhanXoa = hopThoaiLuaChon(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5)/2, mess.length() + 10, 5 );
						if(xacNhanXoa == 1){
							xoaNodeNhanVien(rootNV, p->nhanVien.maNhanVien);
							string mess2 = "Da xoa Nhan Vien!";
							thongBao(mess2,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, mess.length() + 10, 5);
							
							tongTrang = tongSoTrangNhanVien(rootNV);		
							if (trang > 1 && vtLuaChon == 1){
								trang--;
								vtLuaChon = 10;
							} else if (vtLuaChon > 1) vtLuaChon--;
						}
					}
				}
				// ve form danh sach
				// Nap du lieu vao ban
				veKhungDanhSachNhanVien();
				xoaDuLieuTrongBangNhanVien();
				doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);
					
				// Xoa con tro
				gotoxy(toaDoX , toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				// Gan vi tri moi cho con tro
				vtLuaChon = 1;	
				// Ve con tro
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
	
			}else if(c == KEY_F5){
				int vtNhanVien = (trang - 1) * 10 + vtLuaChon - 1;
				TreeNhanVien p = timKiemNhanVienTheoViTri(rootNV, vtNhanVien);
				giaoDienHoaDon(rootNV, p->nhanVien, dsVT);
			
				veKhungDanhSachNhanVien();
				xoaDuLieuTrongBangNhanVien();
				doDuLieuRaBangNhanVien(rootNV, tongTrang, trang);
					
				gotoxy(toaDoX , toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				vtLuaChon = 1;	
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
			}	
		} while (c != KEY_ESC);		
	}
}

//int main(){
//	TreeNhanVien rootNV;
//	rootNV = NULL;
//
//	NhanVien nv1;
//	nv1.maNhanVien = "NV1";
//	nv1.ho = "nguyen";
//	nv1.ten ="a";
//	nv1.phai = 1;
//	nv1.hoaDonFirst = NULL;
//	
//	NhanVien nv4;
//	nv4.maNhanVien = "NV4";
//	nv4.ho = "tran";
//	nv4.ten ="b";
//	nv4.phai = 0;
//	nv4.hoaDonFirst = NULL;
//	 
//	NhanVien nv3;
//	nv3.maNhanVien = "NV3";
//	nv3.ho = "nguyen";
//	nv3.ten ="t";
//	nv3.phai = 1;
//	nv3.hoaDonFirst = NULL;
//	
//	NhanVien nv2;
//	nv2.maNhanVien = "NV2";
//	nv2.ho = "nguyen";
//	nv2.ten ="g";
//	nv2.phai = 1;
//	nv2.hoaDonFirst = NULL;
//	
//	NhanVien nv6;
//	nv6.maNhanVien = "NV6";
//	nv6.ho = "nguyen";
//	nv6.ten ="a";
//	nv6.phai = 1;
//	nv6.hoaDonFirst = NULL;
//	
//	NhanVien nv5;
//	nv5.maNhanVien = "NV5";
//	nv5.ho = "tran";
//	nv5.ten ="b";
//	nv5.phai = 0;
//	nv5.hoaDonFirst = NULL;
//
//	NhanVien nv7;
//	nv7.maNhanVien = "NV7";
//	nv7.ho = "nguyen";
//	nv7.ten ="t";
//	nv7.phai = 1;
//	nv7.hoaDonFirst = NULL;
//	
//	NhanVien nv8;
//	nv8.maNhanVien = "NV8";
//	nv8.ho = "nguyen";
//	nv8.ten ="g";
//	nv8.phai = 1;
//	nv8.hoaDonFirst = NULL;	
//
//	NhanVien nv11;
//	nv11.maNhanVien = "NV11";
//	nv11.ho = "tran";
//	nv11.ten ="b";
//	nv11.phai = 0;
//	nv11.hoaDonFirst = NULL;
//
//	NhanVien nv10;
//	nv10.maNhanVien = "NV10";
//	nv10.ho = "nguyen";
//	nv10.ten ="t";
//	nv10.phai = 1;
//	nv10.hoaDonFirst = NULL;
//	
//	NhanVien nv9;
//	nv9.maNhanVien = "NV9";
//	nv9.ho = "nguyen";
//	nv9.ten ="g";
//	nv9.phai = 1;
//	nv9.hoaDonFirst = NULL;	
//	Insert_Node(rootNV, nv1);
//	Insert_Node(rootNV, nv2);
//	Insert_Node(rootNV, nv3);
//	Insert_Node(rootNV, nv4);
//	
//	Insert_Node(rootNV, nv5);
//	Insert_Node(rootNV, nv6);
//	Insert_Node(rootNV, nv7);
//	Insert_Node(rootNV, nv8);
//
//	Insert_Node(rootNV, nv9);
//	Insert_Node(rootNV, nv10);
//	Insert_Node(rootNV, nv11);
//	
//	giaoDienNhanVien(rootNV);
//
//	return 0;
//}

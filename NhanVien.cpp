 #include "HoaDon.cpp"


string tenCotBangNhanVien[] = {"STT", "MA NHAN VIEN", "HO NHAN VIEN", "TEN NHAN VIEN", "PHAI"};
string tenThuocTinhNhanVien[] = {"Ma Nhan Vien", "Ho Nhan Vien", "Ten Nhan Vien", "Phai(1: NAM; 0: NU)"};

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

void testLNR_MA_NhanVien(TreeNhanVien &rootNV){
	if(rootNV != NULL){
		testLNR_MA_NhanVien(rootNV->nvLeft);
		cout << rootNV->nhanVien.maNhanVien << endl;
		PTRHoaDon hoaDonFirst = new NodeHoaDon;
		hoaDonFirst = rootNV->nhanVien.hoaDonFirst;
		while(hoaDonFirst != NULL){
			cout << "Ma Hoa Don :  "<< hoaDonFirst->hoaDon.soHoaDon << endl;
			
			PTR_CT_HoaDon ctHoaDon = new Node_ChiTiet_HD;
			ctHoaDon = hoaDonFirst->hoaDon.CT_HD_First;
			while(ctHoaDon != NULL){
				cout << "Ma VT trong chi tiet HD : " << ctHoaDon->chiTietHD.maVT << endl;
				ctHoaDon = ctHoaDon->CT_HD_Next;
			}
			hoaDonFirst = hoaDonFirst->HD_Next;	
		}
		
		testLNR_MA_NhanVien(rootNV->nvRight);
	}
}

void testInorder(TreeNhanVien &rootNV){
	if(rootNV != NULL){
		testInorder(rootNV->nvLeft);
		cout << rootNV->nhanVien.maNhanVien << endl;
		testInorder(rootNV->nvRight);
	}
}

void initStackNhanVien(StackNV &sp){
	sp = NULL;
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
	TreeNhanVien p;
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
				cout << res;getch();
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
//int main(){
//	TreeNhanVien rootNV;
//	rootNV = NULL;
//	themMotNhanVien(rootNV);
//		themMotNhanVien(rootNV);
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
//	 //THEM OK
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
//	Insert_Node(rootNV, nv1);
//	Insert_Node(rootNV, nv2);
//	Insert_Node(rootNV, nv3);
//	Insert_Node(rootNV, nv4);
//	
//	return 0;
//}

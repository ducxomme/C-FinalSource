#include "NhanVien.cpp"

string dsChucNang[]={"VAT TU", "NHAN VIEN", "IN HOA DON", "DANH SACH VAT TU XUAT CAO NHAT"};


char thucdon [so_item][50] = {"1. Nhap Vat Tu                   ",
							  "2. In danh sach vat tu ton kho   ",	
			                  "3. Nhap Nhan Vien                ",
			                  "4. In danh sach Nhan Vien        ",
			                  "5. Thong Ke Hoa Don              ",
			                  "6. Danh sach vat tu xuat cao nhat",
			                  "7. Thoat                         "
			                  };









void LuuFile(TreeNhanVien &root){
	ofstream myFile;
	myFile.open("dsNV.txt");
	
	StackNV sp = NULL;
	TreeNhanVien p = root;
	PTRHoaDon ptrHD;
	PTR_CT_HoaDon ptrCTHD;
	
	while(p != NULL){
		myFile << "===NV" << endl;
		// Nhan Vien
		myFile << p->nhanVien.maNhanVien << endl;
		myFile << p->nhanVien.ho << endl;
		myFile << p->nhanVien.ten << endl;
		myFile << (int)p->nhanVien.phai << endl;
		
		// Hoa Don
		ptrHD = p->nhanVien.hoaDonFirst;
		while(ptrHD != NULL){
			myFile << "===HD" << endl;
			myFile << ptrHD->hoaDon.soHoaDon << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.ngay << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.thang << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.nam << endl;
			myFile << ptrHD->hoaDon.loai << endl;
			
			// Chi Tiet Hoa Don
			PTR_CT_HoaDon ptrCTHD = ptrHD->hoaDon.CT_HD_First;
			while(ptrCTHD != NULL){
				myFile << "===CTHD" << endl;
				myFile << ptrCTHD->chiTietHD.maVT << endl;
				myFile << ptrCTHD->chiTietHD.soLuong << endl;
				myFile << ptrCTHD->chiTietHD.donGia << endl;
				myFile << ptrCTHD->chiTietHD.vat << endl;
				
				ptrCTHD = ptrCTHD->CT_HD_Next;
			}	
			ptrHD = ptrHD->HD_Next;
		}
			
		if(p->nvRight != NULL)
			push(sp, p->nvRight);
		if(p->nvLeft != NULL)
			p=p->nvLeft;
		else 
			if(sp == NULL)
				break;
			else pop(sp, p);		
	}
	myFile << "===END";
	myFile.close();
}

void DocFile(TreeNhanVien &root){
	ifstream myFile;
	myFile.open("dsNV.txt");
	if(!myFile){
		cout << "Khong the mo file";
		return;
	}
	
	string s;
	NhanVien nv;
	HoaDon hd;
	ChiTiet_HD ctHD;
	int phai;
	
	getline(myFile, s);
	if(s == "===END")
		return;
		
	while(!myFile.eof()){
NHANVIEN:	
		getline(myFile, nv.maNhanVien);
		getline(myFile, nv.ho);
		getline(myFile, nv.ten);
		getline(myFile, s);
		stringstream(s) >> phai;
		nv.phai = (phai == 1) ? 1 : 0;		
		nv.hoaDonFirst = NULL;
			
		getline(myFile, s);
		if(s == "===END"){
			Insert_Node(root, nv);
			return;
		}
		else if(s == "===NV")
			goto NHANVIEN;	
			
HOADON:
		getline(myFile, hd.soHoaDon);
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.ngay;
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.thang;
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.nam;
		getline(myFile, s);
		hd.loai = s[0];
		hd.CT_HD_First = NULL;
		
		
		getline(myFile, s);
		if(s == "===END"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			return;
		}
		else if(s == "===HD"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			goto HOADON;
			
		}
		else if(s == "===NV"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			goto NHANVIEN;
		}
			

CTHOADON:
		getline(myFile, ctHD.maVT);
		getline(myFile, s);
		stringstream(s) >> ctHD.soLuong;
		getline(myFile, s);
		stringstream(s) >> ctHD.donGia;
		getline(myFile, s);
		stringstream(s) >> ctHD.vat;
		
		insertCTHoaDonLast(hd.CT_HD_First, ctHD);
		getline(myFile, s);
		if(s == "===CTHD"){
			goto CTHOADON;
		}
		else if(s == "===NV"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			goto NHANVIEN;
		}
		else if (s == "===HD"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			goto HOADON;
		}
		else if(s == "===END"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			return;			
		}
			
	}
	myFile.close();
}

void MenuDong(TreeNhanVien &rootNV, DSVatTu &dsVT, char td [so_item][50]){
X:	Normal();
	system("cls");   int chon =0;
	int i; 
	veHinhChuNhat(cot, 7, 33, 3, 4);
	gotoxy(cot + 10, 8);
	SetBGColor(4);
	cout << "QUAN LY VAT TU";
	

	while(true){ 
	Normal();
	for ( i=0; i< so_item ; i++){ 
		gotoxy(cot, dong +i);
	    cout << td[i];
	}
	HighLight();
	gotoxy(cot,dong+chon);
	cout << td[chon];
	int kytu;
	
		kytu = keyPressed();
		if (kytu == KEY_UP) 
		{
		  	Normal();
			gotoxy(cot,dong+chon);
		    cout << td[chon];
		    chon --;
		    if (chon < 0)	chon = so_item - 1;
		    HighLight();
		    gotoxy(cot,dong+chon);
		    cout << td[chon];
		}
		if (kytu == KEY_DOWN)  
		  	{
		  		Normal();
		        gotoxy(cot,dong+chon);
		        cout << td[chon];
		        chon ++;
		        if (chon == so_item) chon = 0;
		        HighLight();
		        gotoxy(cot,dong+chon);
		        cout << td[chon];
		  	}
		if (kytu == KEY_ENTER)
		{
		  	switch(chon)
			{
		  		case 0:
		  			// NHAP VAT TU
		  			themMotVatTu(dsVT);
		  			goto X;
		  			break;
		  		case 1:
				  	// IN DANH SACH VAT TU
				  	giaoDienVatTu(dsVT, rootNV);
				  	goto X;
					break;
				case 2:
					// NHAP NHAN VIEN
					themMotNhanVien(rootNV);
					goto X;
					break;
				case 3:
					// IN DS NHAN VIEN
					giaoDienNhanVien(rootNV);
					goto X;
					break;
				case 4:
					// THONG KE HOA DON 	
					goto X;
					break;
				case 5:
					// LIET KE VAT TU BAN CHAY
					goto X;
					break;
				case 6:
					// THOAT
					LuuFile(rootNV);
					saveFileVatTu(dsVT);
					SetColor(WHITE);
					SetBGColor(BLACK);
					system("cls");
					exit(1);
			}
		}
	}
}

int main(){
//	// Chi tiet HD
//	PTR_CT_HoaDon ctHoaDonFirst1 = new Node_ChiTiet_HD;
//	ctHoaDonFirst1 = NULL;
//	
//	// Chi Tiet HD1
//	ChiTiet_HD cthd1;
//	cthd1.maVT = "VT2";
//	cthd1.soLuong = 100;
//	cthd1.donGia = 200000;
//	cthd1.vat = 3;
//	insertCTHoaDonLast(ctHoaDonFirst1, cthd1);
//	
//	// Chi tiet HD2
//	ChiTiet_HD cthd2;
//	cthd2.maVT = "VT1";
//	cthd2.soLuong = 500;
//	cthd2.donGia = 200;
//	cthd2.vat = 6;
//	insertCTHoaDonLast(ctHoaDonFirst1, cthd2);
//	
//	// Hoa Don
//	PTRHoaDon hoaDonFirst1 = new NodeHoaDon;
//	hoaDonFirst1 = NULL;
//	
//	Date d;
//	HamTraVeCurrentTime(d);
//		
//	HoaDon hd1;
//	hd1.soHoaDon = "HD1";
//	hd1.loai = 'N';
//	hd1.ngayLapHoaDon = d;
//	hd1.CT_HD_First = ctHoaDonFirst1;
//	insertNodeHoaDon(hoaDonFirst1, hd1);	
//	
//	// Nhan Vien
//	TreeNhanVien treeNV = new NodeNhanVien;
//	treeNV = NULL;
//	
//	// NV1
//	NhanVien nv1;
//	nv1.maNhanVien = "NV1";
//	nv1.ho = "Nguyen";
//	nv1.ten = "Duc";
//	nv1.phai = 1;
//	nv1.hoaDonFirst = hoaDonFirst1;
//	Insert_Node(treeNV, nv1);
//	
//	
//	// Chi tiet HD cua NV2
//	PTR_CT_HoaDon ctHoaDonFirst2 = new Node_ChiTiet_HD;
//	ctHoaDonFirst2 = NULL;
//	
//	// Chi Tiet HD1
//	ChiTiet_HD cthd3;
//	cthd3.maVT = "VT2";
//	cthd3.soLuong = 100;
//	cthd3.donGia = 200000;
//	cthd3.vat = 3;
//	insertCTHoaDonLast(ctHoaDonFirst2, cthd3);	
//	
//	PTRHoaDon hoaDonFirst2 = new NodeHoaDon;
//	hoaDonFirst2 = NULL;
//	
//	HoaDon hd5;
//	hd5.soHoaDon = "HD5";
//	hd5.loai = 'N';
//	hd5.ngayLapHoaDon = d;
//	hd5.CT_HD_First = ctHoaDonFirst2;
//	insertNodeHoaDon(hoaDonFirst2, hd5);
//	//NV2
//	NhanVien nv2;
//	nv2.maNhanVien = "NV7";
//	nv2.ho = "Tran";
//	nv2.ten = "Khang";
//	nv2.phai = 1;
//	nv2.hoaDonFirst = hoaDonFirst2;
//	
//	
//	Insert_Node(treeNV, nv2);
	
	//LuuFile(treeNV);
		
	TreeNhanVien rootNV;
	rootNV = NULL;
	DocFile(rootNV);
	
	DSVatTu dsVT;
	dsVT.soLuongVatTu = 0;
	loadFileVatTu(dsVT);

  	int chon;  
    MenuDong (rootNV, dsVT, thucdon);
//        
//	StackNV sp = NULL;
//	TreeNhanVien p = rootNV;
//	if(p == NULL) return 0;
//	do{
//		while(p != NULL){
//			push(sp, p);
//			p=p->nvLeft;
//		}
//		
//		if(sp != NULL){
//			pop(sp, p);
//			cout << "======NV" << endl;
//			cout << p->nhanVien.maNhanVien << endl;
//			PTRHoaDon ptrHD = p->nhanVien.hoaDonFirst;
//			
//			while(ptrHD != NULL){
//				cout << "===HD" << endl;
//				cout << ptrHD->hoaDon.soHoaDon << endl;
//				PTR_CT_HoaDon ptrCtHD = ptrHD->hoaDon.CT_HD_First;
//				while(ptrCtHD != NULL){
//					cout << "=CTHD" << endl;
//					cout << ptrCtHD->chiTietHD.maVT << endl;
//					ptrCtHD = ptrCtHD->CT_HD_Next;
//				}
//				ptrHD = ptrHD->HD_Next;
//			}
//			p=p->nvRight;
//		}
//		else break;
//	}while(1);
//	//LuuFile(rootNV);        		
	return 0;
}



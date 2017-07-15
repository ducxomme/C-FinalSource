 #include "HoaDon.cpp"

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

void Insert_Node(TreeNhanVien &rootNV, NhanVien nv){
	if(rootNV == NULL){
		rootNV = getNodeNhanVien(nv);
	}
	else{
		if(nv.maNhanVien == rootNV->nhanVien.maNhanVien)	
			return;
		else if(nv.maNhanVien < rootNV->nhanVien.maNhanVien)
			Insert_Node(rootNV->nvLeft, nv);
		else 
			Insert_Node(rootNV->nvRight, nv);
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
//  CHUYEN CAY NHI PHAN SANG STACK DSLKD
//struct StackNhanVien{
//	TreeNhanVien nodeNV;
//	struct StackNhanVien *next;
//};
//typedef struct StackNhanVien *StackNV;

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



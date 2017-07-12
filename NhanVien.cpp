 #include "DuLieu.cpp"

int EmptyTreeNV(TreeNhanVien &rootNV){
	return (rootNV == NULL ? 1 : 0);
}

void InitNhanVien(TreeNhanVien &rootNV){
	rootNV = NULL;
}

TreeNhanVien getNodeNhanVien(NhanVien nv){
	TreeNhanVien treeNV = new dsNhanVien;
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
		testLNR_MA_NhanVien(rootNV->nvRight);
	}
}



int main(){
	
	TreeNhanVien rootNV;
	InitNhanVien(rootNV);
	
	NhanVien nv1;
	nv1.maNhanVien = "NV2";
	nv1.ho = "Nguyen";
	nv1.ten = "A";
	nv1.phai = true;
	nv1.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv1);
	NhanVien nv2;
	nv2.maNhanVien = "NV4";
	nv2.ho = "Nguyen";
	nv2.ten = "B";
	nv2.phai = false;
	nv2.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv2);
	NhanVien nv3;
	nv3.maNhanVien = "NV1";
	nv3.ho = "Nguyen";
	nv3.ten = "A";
	nv3.phai = true;
	nv3.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv3);
	NhanVien nv4;
	nv4.maNhanVien = "NV3";
	nv4.ho = "Tran";
	nv4.ten = "C";
	nv4.phai = true;
	nv4.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv4);
	NhanVien nv5;
	nv5.maNhanVien = "NV6";
	nv5.ho = "Nguyen";
	nv5.ten = "A";
	nv5.phai = true;
	nv5.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv5);
	NhanVien nv6;
	nv6.maNhanVien = "NV5";
	nv6.ho = "Nguyen";
	nv6.ten = "A";
	nv6.phai = true;
	nv6.hoaDonFirst = NULL;
	Insert_Node(rootNV, nv6);
	xoaNodeNhanVien(rootNV, "NV8");
	testLNR_MA_NhanVien(rootNV);
	return 0;
}


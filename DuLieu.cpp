#include "System.cpp"
#define MAX_VT 100
struct VatTu{
	string maVatTu;
	string tenVatTu;
	string donViTinh;
	int soLuongTon;
};

struct dsVatTu{
	int soLuongVatTu;
	VatTu nodesVT[MAX_VT];
};
typedef struct dsVatTu DSVatTu;

struct ChiTiet_HD{
	string maVT;
	int soLuong;
	int donGia;
	int vat;
};

struct Node_ChiTiet_HD{
	ChiTiet_HD chiTietHD;
	struct Node_ChiTiet_HD *CT_HD_Next;	
};
typedef struct Node_ChiTiet_HD *PTR_CT_HoaDon;


struct HoaDon{
	string soHoaDon;
	Date ngayLapHoaDon;
	char loai;
	PTR_CT_HoaDon CT_HD_First;
};

struct NodeHoaDon{
	HoaDon hoaDon;
	struct NodeHoaDon *HD_Next;
};
typedef struct NodeHoaDon *PTRHoaDon;

struct NhanVien{
	string maNhanVien;
	string ho;
	string ten;
	bool phai;
	PTRHoaDon hoaDonFirst;
};

struct NodeNhanVien{
	NhanVien nhanVien;
	struct NodeNhanVien *nvLeft;
	struct NodeNhanVien *nvRight;
};
typedef struct NodeNhanVien *TreeNhanVien;





// Functions cua ============= VAT TU
int kiemTraRongVatTu(DSVatTu &ds_VT);
int kiemTraDayVatTu(DSVatTu &ds_VT);
int timViTriVatTuTrung(DSVatTu &ds_VT, string maVT);
int timViTriThemVatTu(DSVatTu ds_VT, string maVT);
int themVatTuVaoViTri(DSVatTu &ds_VT, VatTu vatTu);
int xoaVatTu(DSVatTu &ds_VT, string maVT);
void sapXepTenVatTuTangDan(DSVatTu &ds_VT);
void saveFileVatTu(DSVatTu &ds_VT);
void loadFileVatTu(DSVatTu &ds_VT);


void DocFile(TreeNhanVien &root);


//  Cac Functions cua ========== NHAN VIEN

// STACK CHUA DS TREENhanVien
struct StackNhanVien{
	TreeNhanVien nodeNV;
	struct StackNhanVien *next;
};
typedef struct StackNhanVien *StackNV;

int EmptyTreeNV(TreeNhanVien &rootNV);
void InitNhanVien(TreeNhanVien &rootNV);
bool Insert_Node(TreeNhanVien &rootNV, NhanVien nv);
void timNodeNVTheMang(TreeNhanVien &nodeNVRight);
void xoaNodeNhanVien(TreeNhanVien &rootNV, string maNV);
TreeNhanVien search_NhanVien(TreeNhanVien &rootNV, string maNV);
void testLNR_MA_NhanVien(TreeNhanVien &rootNV);
int push(StackNV &sp, TreeNhanVien nv);
int pop(StackNV &sp, TreeNhanVien &nv);



// Cac Functions cua ============= HOA DON
int emptyDSHoaDon(PTRHoaDon hoaDonFirst);
void InitHoaDon(PTRHoaDon &hoaDonFirst);
PTRHoaDon getNodeHoaDon(HoaDon hd);
bool insertNodeHoaDon(PTRHoaDon &hoaDonFirst, HoaDon hd);
PTRHoaDon timKiemHoaDonTheoMa(PTRHoaDon &hoaDonFirst, string maHD);
int deleteFirstHD(PTRHoaDon &hoaDonFirst);
int deleteAfterHD(PTRHoaDon p);
int deleteInfoHD(PTRHoaDon &hoaDonFirst, string maHD);
void veGiaoDienThongKeHoaDon();
void xoaDuLieuTrongBangThongKe();
void doDuLieuRaBangThongKeHoaDon(TreeNhanVien &rootNV, PTRHoaDon &ptrHD, int tongTrang, int trang);


// Cac Functions cua ============= CHI TIET HOA DON
int kiemTraRongCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst);
void InitCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst);
PTR_CT_HoaDon getNodeCTHoaDon(ChiTiet_HD ctHD);
int insertCTHoaDonLast(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD);
int insertCTHoaDonFirst(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD);
int deleteFirstCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst);
int deleteAfterCTHoaDon(PTR_CT_HoaDon p);
PTR_CT_HoaDon timViTriCoMaVT(PTR_CT_HoaDon ctHoaDonFirst, string maVT);
int deleteCTHoaDonTheoMaVT(PTR_CT_HoaDon &ctHoaDonFirst, string maVT);
int demSoChiTietHD(PTR_CT_HoaDon ctHoaDonFirst);
void duyetDanhSach(PTR_CT_HoaDon first);
void danhSachCacVatTuDaNhap(PTRHoaDon ptrHD);
void giaoDienCacVatTuDaNhap(PTR_CT_HoaDon &ptrCTHD);
void veKhungChiTietHoaDonDaLap(TreeNhanVien &rootNV, PTRHoaDon ptrHD);

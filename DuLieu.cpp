#include "System.cpp"
#define MAX 100

struct VatTu{
	string maVatTu;
	string tenVatTu;
	string donViTinh;
	int soLuongTon;
};

struct dsVatTu{
	int soLuongVatTu;
	VatTu nodesVT[MAX];
};
typedef struct dsVatTu DSVatTu;

struct ChiTiet_HD{
	string maVT;
	int soLuong;
	long donGia;
	double vat;
};

struct ds_ChiTiet_HD{
	ChiTiet_HD chiTietHD;
	struct ds_ChiTiet_HD *CT_HD_Next;	
};
typedef struct ds_ChiTiet_HD *PTR_CT_HoaDon;

struct Date{
	int ngay;
	int thang;
	int nam;
};
typedef struct Date date;

struct HoaDon{
	string soHoaDon;
	date ngayLapHoaDon;
	char loai;
	PTR_CT_HoaDon CT_HD_First;
};

struct dsHoaDon{
	HoaDon hoaDon;
	struct dsHoaDon *HD_Next;
};
typedef struct dsHoaDon *PTRHoaDon;

struct NhanVien{
	string maNhanVien;
	string ho;
	string ten;
	bool phai;
	PTRHoaDon hoaDonFirst;
};

struct dsNhanVien{
	NhanVien nhanVien;
	struct dsNhanVien *nvLeft;
	struct dsNhanVien *nvRight;
};
typedef struct dsNhanVien *TreeNhanVien;




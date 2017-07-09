struct VatTu{
	int maVatTu;
	string tenVatTu;
	string donViTinh;
	int soLuongTon;
};

struct dsVatTu{
	int soLuongVatTu;
	VatTu dsVT[MAX];
};
typedef struct dsVatTu ds_VatTu;

struct ChiTiet_HD{
	int maVT;
	int soLuong;
	long donGia;
	double vat;
};

struct ds_ChiTiet_HD{
	ChiTiet_HD chiTietHD;
	struct ChiTiet_HD *CT_HD_Next;	
};
typedef struct ds_ChiTiet_HD *PTR_CT_HoaDon;

struct Date{
	int ngay;
	int thang;
	int nam;
};
typedef struct Date date;

struct HoaDon{
	int soHoaDon;
	date ngayLapHoaDon;
	char loai;
	PTR_CT_HoaDon CT_HD_First;
};

struct dsHoaDon{
	HoaDon hoaDon;
	struct HoaDon *HD_Next;
};
typedef struct dsHoaDon *PTRHoaDon;

struct NhanVien{
	int maNhanVien;
	string ho;
	string ten;
	string phai;
	PTRHoaDon hoaDonFirst;
};

struct dsNhanVien{
	NhanVien nhanVien;
	struct nhanVien *nvLeft;
	struct nhanVien *nvRight;
};
typedef struct dsHoaDon *treeNhanVien;



//void Xoa();

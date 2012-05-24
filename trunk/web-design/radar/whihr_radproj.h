// RadProjection.h: interface for the CRadEPrj class.
//���ǵ�������ϵ�Ķ�λ���״�����ת��Ϊ��γ��������
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADPROJECTION_H__B0D62835_14C8_41CB_A125_5FE50444D39E__INCLUDED_)
#define AFX_RADPROJECTION_H__B0D62835_14C8_41CB_A125_5FE50444D39E__INCLUDED_

#if !defined (__PI_VALUE__)
#define __PI_VALUE__
#define PI 3.1415927
#endif

//--------------------  ��������ϵ��λ���� ---------------------------
class CEarth  
{
public:
	double r_numda, r_phy, r_h;
	double EarthRadius, r_res ;
	int rx, ry; 
public:
//���ݾ�γ��ֵ�����㷽λ�͵��Ľ�
	void geo2polar(double phy, double delta_numda, double &beta, double &theta);
	void polar2geo(double beta, double theta, double &phy, double &delta_numda);

	void arcS_of_gps(double Az, double S,double& lon, double& lat);
	void gps_to_Azimuth(double lon, double lat, double& Az, double& beta);
	void gps_to_arcS(double lon, double lat, double& Az, double& S);
	void gps_to_arcS(double lon,double lat, int& sx, int& sy);

	//constructor
	CEarth();
	virtual ~CEarth();
};


//--------------------  ��Ч����������뾶���ƶ�λ���� ---------------------------
class CRadEPrj : public CEarth
{
private:
	double Km;
public:
	void Initialized(double dNdz, int x0, int y0, int res);

	//�����״�ز��������Ŀ����ĵ�������
	void tilt_of_gps(double e, double dl, double& dh, double& dS);
	void tilt_of_gps(double e,  double az, double dl,\
					double& lon, double& lat,double& dh,double& dS );

	void tilt_of_gps(double e, int i, int j, double& lon, double& lat,\
					double& dh, double& dS) ;

	//���ݾ�γ��ֵ�����������㷽λ������
	void gps_to_tilt(double lon, double lat,double e, double& Az, double& L,double& H );
	void gps_to_tilt(double lon,double lat,double e, double& x, double& y);
	
	void DEM_to_tilt(double lon, double lat, double h, \
			double& ele, double& az ,double& L,double& S) ;

	void ES_of_H(double e, double dS, double& dh);
	void HS_of_E(double H, double dS, double& ele);

//���ݼ��㲨���߶�
	void RayPath_of_SH(double e, int Bins, short *S, short *H );

	//constructor
	CRadEPrj(double lon, double lat, double h);
	virtual ~CRadEPrj();

};
#endif // !defined(AFX_RADPROJECTION_H__B0D62835_14C8_41CB_A125_5FE50444D39E__INCLUDED_)

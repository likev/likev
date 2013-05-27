load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/shea_util.ncl"
begin
	imgname = "fnl_20100903_18-700map"

	wks_type = "png"
	wks_type@wkWidth = 800
	wks_type@wkHeight = 600

;;imgname   
;;wkWidth
;;wkHeight
   
   wks = gsn_open_wks(wks_type,imgname)
   gsn_define_colormap(wks,"amwg");"WhBlGrYeRe");"WhViBlGrYeOrRe")
   cmap = gsn_retrieve_colormap(wks)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ;add file
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      diri = "./"
      fili = "changjiang.txt"
      nlvl = 270  
      ncol = 2
     TestData = asciiread (diri+fili , (/nlvl,ncol/), "float")  
      x = TestData (:,0)
      y = TestData (:,1)
      hfili = "huanghe.txt"
      nlvl = 270  
      ncol = 2
     hTestData = asciiread (diri+hfili , (/nlvl,ncol/), "float")  
      hx = hTestData (:,0)
      hy = hTestData (:,1)

	fnlname = "fnldata/2011/fnl_20110624_00_00_c.grb";
;;fnlname
   a = addfile(fnlname,"r")

A = new((/48/),integer)
do i=0,23
 A(i) = i
end do
 do i=7,7
   t = a->TMP_3_ISBL_10(A(i),:,:) 
   t=t-273                   
   u = a->U_GRD_3_ISBL_10 (A(i),:,:)  
   v = a->V_GRD_3_ISBL_10(A(i),:,:)  
   H = a->HGT_3_ISBL_10(A(i),:,:)  
   wrf_smooth_2d( t, 3)  
   wrf_smooth_2d( H, 3 )  
   Time=u@initial_time
   p=t@lv_ISBL3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;map
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  res = True
  res@vpXF            = 1  
  res@vpYF            = 1
  res@vpWidthF        = 1
  res@vpHeightF       = 1
  res@cnInfoLabelOn   = False   
  res@gsnLeftString   = ""
  res@gsnCenterString = ""
  res@gsnRightString  = ""
  res@tiXAxisString   = ""

 res@tfDoNDCOverlay=False;True

  res@mpProjection        = "LambertConformal"
  res@mpDataBaseVersion="MediumRes"
  res@mpFillOn       = True
  ;res@mpDataSetName="Earth..4"
  res@mpOutlineSpecifiers=(/"China.states"/)
  res@mpSpecifiedFillColors = "White"
  res@mpOutlineOn           = True
  res@mpLandFillColor       = "White";"yellow green"
  res@mpInlandWaterFillColor = "light sky blue";"PaleTurquoise3"
  res@mpOceanFillColor       = "light sky blue";"PaleTurquoise3"
  res@mpGridAndLimbOn   = True   
  res@gsnMaximize = True             
  res@gsnAddCyclic = False   
  res@mpPerimOn         = True         
  res@mpGridLatSpacingF = 5           
  res@mpGridLonSpacingF = 5  
  ;res@mpGridLineDashPattern  = 2     
  res@mpGridLineThicknessF = 0.05
  res@mpGridLineColor = "brown"
  res@mpMinLatF  = 0                
  res@mpMaxLatF  = 90                
  res@mpMinLonF = 0              
  res@mpMaxLonF = 180
  res@mpLambertParallel1F =  30.0
  res@mpLambertParallel2F =  60.0
  res@mpLambertMeridianF  = 105   
  res@mpLimitMode       = "Corners" 
  res@mpLeftCornerLatF  = -2
  res@mpLeftCornerLonF  = 62
  res@mpRightCornerLatF = 50
  res@mpRightCornerLonF = 175             
  res@tmXBLabelFontHeightF = 0.008
  res@tmXBMajorLengthF     = -0.001
  res@pmTickMarkDisplayMode = "Always" 
  res@gsnDraw=False
  res@gsnFrame=False



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ; plot temp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  tres=res
  tres@cnLevelSelectionMode  = "ManualLevels"    
  tres@cnMinLevelValF        =  200-273              
  tres@cnMaxLevelValF        =  350-273           
  tres@cnLevelSpacingF       =  4         
  tres@cnLineColor = "red"
  tres@cnLineThicknessF =2
  tres@cnHighLabelsOn = True
  tres@cnLowLabelsOn = True
  tres@cnLowLabelFontColor  = "red"
  tres@cnHighLabelFontColor  = "red"
  tres@cnLineLabelFontColor  = "red"
  tres@cnLineDashSegLenF     = 0.18         
  tres@cnLineLabelInterval        = 2
  tres@cnLineLabelFontHeightF   = 0.010 
  tres@cnInfoLabelFontHeightF   = 0.008 
  tres@cnLineLabelPlacementMode   = "constant" 
  tres@lbLabelFontHeightF  = 0.010
  tem = gsn_csm_contour(wks,t,tres)  


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ;  plot Hight
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  hres=res 
  hres@cnLineColor = "blue"
  hres@cnLineThicknessF =2
  hres@cnLineDashSegLenF     = 0.18         
  hres@cnLineLabelInterval        = 3
  hres@cnLineLabelFontHeightF   = 0.010 
  hres@cnInfoLabelFontHeightF   = 0.008 
  hres@cnLineLabelPlacementMode   = "constant" 
  hres@lbLabelFontHeightF  = 0.010
  hres@cnLineLabelFontColor  = "blue"
  hres@cnHighLabelsOn = True
  hres@cnLowLabelsOn = True
  hres@cnLowLabelFontColor  = "blue"
  hres@cnHighLabelFontColor  = "blue"
  hres@cnHighLabelBackgroundColor = -1
  hres@cnHighLabelFontHeightF   = 0.013  
  hres@cnMinLevelValF  = 4000              
  hres@cnMaxLevelValF  = 600            
  hres@cnLevelSpacingF = 40 
       
  hight=  gsn_csm_contour(wks,H,hres)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ; plot Wind
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  wres=res
  wres@vcRefLengthF  = 0.010        
  wres@vcGlyphStyle  = "WindBarb" ;"CurlyVector"    
  wres@vcWindBarbTickLengthF  = 0.3              
  wres@vcWindBarbTickSpacingF  = 0.14 
  wres@vcRefMagnitudeF    = 4    
  wres@vcMinDistanceF   = 0.017  
  wres@vcRefAnnoOrthogonalPosF = -0.08
  wres@vcRefAnnoParallelPosF    =  0.09
  wres@vcRefAnnoFontHeightF     = 0.008

  wind=gsn_csm_vector(wks,u,v,wres)

  plot=gsn_csm_map(wks,res) 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;  add luoyang
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      res@gsMarkerColor = "red"
      res@gsMarkerIndex = 1
      res@gsMarkerSizeF = 0.03
      map2= gsn_add_polymarker(wks,plot,112.47,34.63,res)
      lnres = True
      lnres@gsLineThicknessF = 3.0
   
      txres = True
      txres@txFont        = "helvetica-bold"
      txres@txFontColor   = "Blue"
      txres@txFontHeightF = 0.008
      txres@txJust        = "Topright"
      map1=gsn_add_text(wks,plot,"LY",112.47,34.63,txres)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ; overlay
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   overlay(plot,tem)
   overlay(plot,hight) 
   overlay(plot,wind)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;  plot changjiang and huanghe
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   d=new(270*2,graphic)
   d=gsn_add_polyline(wks,plot,x,y,res)
   hd=new(270*2,graphic)
   hd=gsn_add_polyline(wks,plot,hx,hy,res)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ; add text
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   amres=True
   amres@txPerimOn             = True
   amres@txPerimColor          = "Black"
   amres@txPerimThicknessF     = 1.0
   amres@txPerimSpaceF         = 0.8
   amres@txFontHeightF   = 0.01
   amres@txFontColor =  "Blue"
   amres@txPerimOn     = True
   amres@amParallelPosF   = 0.1    
   amres@amOrthogonalPosF = 0.5  
   amres@txBackgroundFillColor = "White"
   time_text = gsn_create_text(wks,"   UTC     "+ Time+"   ",amres)
   amres@amParallelPosF   = 0.39
   amres@amOrthogonalPosF = -0.45
   amres@amJust           = "BottomCenter"
   txt = gsn_add_annotation(plot,time_text,amres)


   mres=True
   mres@txPerimOn             = True
   mres@txPerimColor          = "Black"
   mres@txPerimThicknessF     = 1.0
   mres@txPerimSpaceF         = 0.8
   mres@txFontHeightF   = 0.01
   mres@txFontColor =  "Red"
   mres@txPerimOn     = True
   mres@amParallelPosF   = 0.2   
   mres@amOrthogonalPosF = 0.6 
   mres@txBackgroundFillColor = "White"

   lambert_text = gsn_create_text(wks,p+"(hpa) Temp(C) Hight(gpm)",mres)
   mres@amJust    = "BottomCenter"
   mres@amParallelPosF   = 0.39
   mres@amOrthogonalPosF = -0.40
   txt = gsn_add_annotation(plot,lambert_text,mres)


   draw(plot)
   frame(wks)

  end do

 end

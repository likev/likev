load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/shea_util.ncl"
begin
    imgname = "fnl_2011062400-500map"

    wks_type = "png"
    wks_type@wkWidth = 800
    wks_type@wkHeight = 800

;;imgname   
;;wkWidth
;;wkHeight
   
   wks = gsn_open_wks(wks_type,imgname)
   gsn_define_colormap(wks,"WhBlGrYeRe");"WhViBlGrYeOrRe")"amwg");
   cmap = gsn_retrieve_colormap(wks)

;-----------------------------------------------
   ;add file
;---------------------
      diri = "./"
      fili = "changjiang.txt"
      nlvl = 267  
      ncol = 2
     TestData = asciiread (diri+fili , (/nlvl,ncol/), "float")  
      x = TestData (:,0)
      y = TestData (:,1)
      hfili = "huanghe.txt"
      nlvl = 259  
      ncol = 2
     hTestData = asciiread (diri+hfili , (/nlvl,ncol/), "float")  
      hx = hTestData (:,0)
      hy = hTestData (:,1)

    fnlname = "fnl_20110624_00_00_c.grb";
;;fnlname
   a = addfile(fnlname,"r")

A = new((/48/),integer)
do i=0,23
 A(i) = i
end do
 do i=13,13
   t = a->TMP_3_ISBL_10(A(i),:,:)
   t=t-273                   
   u = a->U_GRD_3_ISBL_10 (A(i),:,:)  
   v = a->V_GRD_3_ISBL_10(A(i),:,:)  
   H = a->HGT_3_ISBL_10(A(i),:,:)  
   wrf_smooth_2d( t, 3)  
   wrf_smooth_2d( H, 3 )  
   Time=u@initial_time
   p=t@lv_ISBL3
   
   rh = a->R_H_3_ISBL_10(A(i),:,:)
   
   
;------------------------------------------------------
  res0 = True
  res0@vpXF            = 1  
  res0@vpYF            = 1
  res0@vpWidthF        = 1
  res0@vpHeightF       = 1
 

  res0@tiXAxisString   = ""

  res0@tfDoNDCOverlay=False;True
 
  res0@gsnDraw=False
  res0@gsnFrame=False
  res0@gsnMaximize = True

;------------------------------------------------------
    ;map
;-----------------------------

  res=res0

  res@mpDataBaseVersion="MediumRes"
  res@mpFillOn       = False ;True
  res@mpDataSetName="Earth..4"
  res@mpOutlineSpecifiers=(/"China.states"/)
  res@mpSpecifiedFillColors = "White"
  res@mpOutlineOn           = True
  res@mpLandFillColor       = "White";"yellow green"
  res@mpInlandWaterFillColor = "light sky blue";"PaleTurquoise3"
  res@mpOceanFillColor       = "light sky blue";"PaleTurquoise3"
  res@mpGridAndLimbOn   = True   
             
   
  res@mpPerimOn         = True         
  res@mpGridLatSpacingF = 5           
  res@mpGridLonSpacingF = 5  
  ;res@mpGridLineDashPattern  = 2     
  res@mpGridLineThicknessF = 0.05
  res@mpGridLineColor = "brown"

  res@mpProjection        = "LambertConformal"
  res@mpMinLatF  = 20                
  res@mpMaxLatF  = 60                
  res@mpMinLonF = 70              
  res@mpMaxLonF = 130

;;mpProjection  
;;mpMinLatF
;;mpMaxLatF
;;mpMinLonF
;;mpMaxLonF

  res@mpLambertParallel1F =  30.0
  res@mpLambertParallel2F =  60.0
  res@mpLambertMeridianF  = 105

;;mpCenterLatF
;;mpCenterLonF
;;mpLambertMeridianF

  res@mpLimitMode       = "LatLon"
 
;  res@mpLeftCornerLatF  = -2
;  res@mpLeftCornerLonF  = 62
;  res@mpRightCornerLatF = 50
;  res@mpRightCornerLonF = 175
             
  res@tmXBLabelFontHeightF = 0.008
  res@tmXBMajorLengthF     = -0.001
  res@pmTickMarkDisplayMode = "Always"
 
  plot=gsn_csm_map(wks,res)

;--------------------------------------------
  res0@gsnLeftString   = ""
  res0@gsnCenterString = ""
  res0@gsnRightString  = ""

 
  res0@gsnAddCyclic = False
 
   
;---------------------------------------------
; plot temp
;---------------------------------------------
  tres=res0
  tres@cnLevelSelectionMode  = "ManualLevels"    
  tres@cnMinLevelValF        =  224-273              
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
 
  tres@cnInfoLabelOn   = False
  tres@cnInfoLabelFontHeightF   = 0.008
  tres@cnLineLabelPlacementMode   = "constant"
  tres@lbLabelFontHeightF  = 0.010

  showtemph = False
;;showtemph

if(showtemph) then
  tem = gsn_csm_contour(wks,t,tres)
  overlay(plot,tem)  
end if

;--------------------------------------------------
 ;  plot Hight
;-------------------------------------------------
  hres=res0
  hres@cnLineColor = "blue"
  hres@cnLineThicknessF =2
  hres@cnLineDashSegLenF     = 0.18         
  hres@cnLineLabelInterval        = 2
  hres@cnLineLabelFontHeightF   = 0.010
 
  hres@cnInfoLabelOn   = False
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
       
  showheight = False
;;showheight

if(showheight) then
  hight=  gsn_csm_contour(wks,H,hres)
  overlay(plot,hight)
end if 
;-------------------------------
;relative
;-------------------------------------
 
 rhres = res0
 
 rhres@gsnSpreadColors = True
 rhres@cnFillOn = True
 rhres@cnLevelSelectionMode  = "ManualLevels"
 rhres@cnMinLevelValF  = 40.0
 rhres@cnMaxLevelValF  = 100.0            
 rhres@cnLevelSpacingF = 10.0
; rhres@cnMonoFillPattern = False
; rhres@cnFillColors = (/"transparent"/)
 rhres@cnFillDrawOrder = "PreDraw"

 rhres@cnLabelBarEndStyle = "ExcludeOuterBoxes"
 
 rhres@lbLabelBarOn = True
 rhres@lbOrientation = "Horizontal" ;"Vertical"
 rhres@lbTopMarginF = 0.01
 rhres@lbBottomMarginF = 0.4
; rhres@lbLabelAngleF = -20
 rhres@lbLabelOffsetF = -0.05

  showhumidity = False
;;showhumidity

if(showhumidity) then 
 relh = gsn_csm_contour(wks,rh,rhres)
 overlay(plot,relh)
end if
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ; plot Wind
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  wres=res0
  wres@vcRefLengthF  = 0.026        
  wres@vcGlyphStyle  = "WindBarb" ;"CurlyVector"    
  wres@vcWindBarbTickLengthF  = 0.4              
  wres@vcWindBarbTickSpacingF  = 0.14
  wres@vcRefMagnitudeF    = 4    
  wres@vcMinDistanceF   = 0.04

  wres@vcRefAnnoOn =  False
  wres@vcRefAnnoOrthogonalPosF = -0.08
  wres@vcRefAnnoParallelPosF    =  0.09
  wres@vcRefAnnoFontHeightF     = 0.008

  u = u*2.5
  v = v*2.5

  showwind = False
;;showwind

if(showwind) then  
  wind=gsn_csm_vector(wks,u,v,wres)
  overlay(plot,wind)
end if
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;  add luoyang
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      mkres = True
      mkres@gsMarkerColor = "red"
      mkres@gsMarkerIndex = 1
      mkres@gsMarkerSizeF = 0.03
      map2= gsn_add_polymarker(wks,plot,112.47,34.63,mkres)
      
      lnres = True
      lnres@gsLineThicknessF = 3.0
   
      txres = True
      txres@txFont        = "helvetica-bold"
      txres@txFontColor   = "Blue"
      txres@txFontHeightF = 0.008
      txres@txJust        = "Topright"
      map1=gsn_add_text(wks,plot,"LY",112.47,34.63,txres)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;  plot changjiang and huanghe
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   lres = True
   lres@gsLineThicknessF = 3.0
   lres@gsLineColor = "grey30"
   
   d=new(270*2,graphic)
   d=gsn_add_polyline(wks,plot,x,y,lres)
   hd=new(270*2,graphic)
   hd=gsn_add_polyline(wks,plot,hx,hy,lres)


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

   amres@txBackgroundFillColor = "White"
   
   Time = str_sub_str(Time,":",".");
   time_text = gsn_create_text(wks, "UTC "+ Time, amres) ;
   
   amres1 = True;
   amres1@amParallelPosF   = 0.5
   amres1@amOrthogonalPosF = -0.5
   amres1@amJust           = "TopRight"
   txt = gsn_add_annotation(plot,time_text,amres1)


   mres=True
   mres@txPerimOn             = True
   mres@txPerimColor          = "Black"
   mres@txPerimThicknessF     = 1.0
   mres@txPerimSpaceF         = 0.8
   mres@txFontHeightF   = 0.01
   mres@txFontColor =  "Red"
   mres@txPerimOn     = True

   mres@txBackgroundFillColor = "White"

   lambert_text = gsn_create_text(wks,p+"(hpa) Temp(C) Hight(gpm)",mres)
   
   mres1 = True
   mres1@amJust    = "TopRight"
   mres1@amParallelPosF   = 0.5
   mres1@amOrthogonalPosF = -0.45
   txt = gsn_add_annotation(plot,lambert_text,mres1)


   draw(plot)
   frame(wks)

  end do

 end


//自定义层

//--- 雨量层 ---
RainOverlay.prototype = new google.maps.OverlayView();

function RainOverlay(map, pointLatlon, text, stationId) {

	// Now initialize all properties.
	this.pointLatlon_ = pointLatlon;
	this.stationId_ = stationId;
	this.map_ = map;
	this.text_ = text;

	// We define a property to hold the image's
	// div. We'll actually create this div
	// upon receipt of the add() method so we'll
	// leave it null for now.
	this.div_ = null;

	// Explicitly call setMap on this overlay
	this.setMap(map);
}

RainOverlay.prototype.onAdd = function() {

	var div = document.createElement('DIV');

	$(div).css({"font-family":"Arial,Helvetica,sans-serif",
				"border":"none",
				"padding":"3px",
				"border-width":"0px",
				"position":"absolute",
				"opacity":"0.8",
				"font-size":"18px",
				"color":"white",
				"background-color":getRainColor(this.text_)//
	});
	//$(div).height(30).width(40);
	$(div).addClass("rain-overlay").attr('stationId',this.stationId_);

	var content = "<span>"+ this.text_ +"</span>";
	$(div).html(content).bind('contextmenu',function(e){
		//return false;
	}).mouseout(function(){
		window.setTimeout("$('#moreinfo').hide();",4000);
	});


	// Set the overlay's div_ property to this DIV
	this.div_ = div;

	// We add an overlay to a map via one of the map's panes.
	// We'll add this overlay to the overlayImage pane.
	var panes = this.getPanes();
	panes.overlayImage.appendChild(this.div_);
}

RainOverlay.prototype.draw = function() {

	// Size and position the overlay. We use a southwest and northeast
	// position of the overlay to peg it to the correct position and size.
	// We need to retrieve the projection from this overlay to do this.
	var overlayProjection = this.getProjection();

	// Retrieve the southwest and northeast coordinates of this overlay
	// in latlngs and convert them to pixels coordinates.
	// We'll use these coordinates to resize the DIV.
	var sw = overlayProjection.fromLatLngToDivPixel(this.pointLatlon_);
	// var ne = overlayProjection.fromLatLngToDivPixel(this.bounds_.getNorthEast());

	// Resize the image's DIV to fit the indicated dimensions.
	var div = this.div_;
	div.style.left = sw.x + 'px';
	div.style.bottom = -sw.y + 'px';
	//div.style.top = ne.y + 'px';
	//div.style.width = (ne.x - sw.x) + 'px';
	//div.style.height = (sw.y - ne.y) + 'px';
}

RainOverlay.prototype.onRemove = function() {
	this.div_.parentNode.removeChild(this.div_);
}

	// Note that the visibility property must be a string enclosed in quotes
RainOverlay.prototype.hide = function() {
	if (this.div_) {
	  this.div_.style.visibility = "hidden";
	}
}

RainOverlay.prototype.show = function() {
	if (this.div_) {
	  this.div_.style.visibility = "visible";
	}
}

RainOverlay.prototype.toggle = function() {
	if (this.div_) {
	  if (this.div_.style.visibility == "hidden") {
		this.show();
	  } else {
		this.hide();
	  }
	}
}

RainOverlay.prototype.toggleDOM = function() {
	if (this.getMap()) {
	  this.setMap(null);
	} else {
	  this.setMap(this.map_);
	}
}

//
function getRainColor(value,hourSpan){
	var colorArray = ["#FFF","#A1EF88","#3CBA3C","#68B5F6","#0000FE","#F700FA","#7F0140"];
	var val = Number(value), hs = Number(hourSpan||12);
	
	if(hs==12){
		if(val==0){
			return colorArray[0];
		}else if(val<5){
			return colorArray[1];
		}else if(val<15){
			return colorArray[2];
		}else if(val<30){
			return colorArray[3];
		}else if(val<70){
			return colorArray[4];
		}else if(val<140){
			return colorArray[5];
		}else{
			return colorArray[6];
		}
	}
	else if(hs==24){
		if(val==0){
			return colorArray[0];
		}else if(val<10){
			return colorArray[1];
		}else if(val<25){
			return colorArray[2];
		}else if(val<50){
			return colorArray[3];
		}else if(val<100){
			return colorArray[4];
		}else if(val<250){
			return colorArray[5];
		}else{
			return colorArray[6];
		}
	}
}

//--- 温度层 ---
TemphOverlay.prototype = new google.maps.OverlayView();

function TemphOverlay(map, pointLatlon, text, stationId) {

	// 初始化.
	this.pointLatlon_ = pointLatlon;
	this.stationId_ = stationId;
	this.map_ = map;
	this.text_ = text;

	this.div_ = null;

	this.setMap(map);
}

TemphOverlay.prototype.onAdd = function() {
	
	//向panes.overlayImage中添加div元素
	var div = document.createElement('DIV');

	$(div).css({"font-family":"Arial,Helvetica,sans-serif",
				"border":"none",
				"padding":"3px",
				"border-width":"0px",
				"position":"absolute",
				"opacity":"0.7",
				"font-size":"18px",
				"color":"red",
				"background-color":"white"//
	});
	//$(div).height(30).width(40);
	$(div).addClass("temph-overlay").attr('stationId',this.stationId_);

	var content = "<span>"+ this.text_ +"</span>";
	$(div).html(content);
	this.div_ = div;

	var panes = this.getPanes();
	panes.overlayImage.appendChild(this.div_);
}

//在指定位置绘制元素
TemphOverlay.prototype.draw = function() {
	
	var overlayProjection = this.getProjection();
	var sw = overlayProjection.fromLatLngToDivPixel(this.pointLatlon_);

	var div = this.div_;
	div.style.left = sw.x-40 + 'px';
	div.style.bottom = -sw.y + 'px';
}

//删除元素
TemphOverlay.prototype.onRemove = function() {
	this.div_.parentNode.removeChild(this.div_);
}

	// Note that the visibility property must be a string enclosed in quotes
TemphOverlay.prototype.hide = function() {
	if (this.div_) {
	  this.div_.style.visibility = "hidden";
	}
}

TemphOverlay.prototype.show = function() {
	if (this.div_) {
	  this.div_.style.visibility = "visible";
	}
}

TemphOverlay.prototype.toggle = function() {
	if (this.div_) {
	  if (this.div_.style.visibility == "hidden") {
		this.show();
	  } else {
		this.hide();
	  }
	}
}

TemphOverlay.prototype.toggleDOM = function() {
	if (this.getMap()) {
	  this.setMap(null);
	} else {
	  this.setMap(this.map_);
	}
}

//--- 风矢量层 ---
WindOverlay.prototype = new google.maps.OverlayView();

function WindOverlay(map, pointLatlon, wind, stationId) {

	this.pointLatlon_ = pointLatlon;
	this.stationId_ = stationId;
	this.map_ = map;
	this.wind_ = wind;

	this.div_ = null;

	this.setMap(map);
}

WindOverlay.prototype.onAdd = function() {

	var wind_canvas = $('<canvas id="myCanvas" width="160" height="160"></canvas>')[0];
	var div = $('<div/>')[0];
	

	$(div).addClass("wind-overlay").attr('stationId',this.stationId_).append(wind_canvas);
	//console.dir(div);
	var dc= wind_canvas.getContext("2d");
	
	drawWind(dc, 80, 80, this.wind_[0], this.wind_[1]);
	
	this.div_ = div;

	var panes = this.getPanes();
	panes.floatShadow.appendChild(this.div_);//overlayImage
}

WindOverlay.prototype.draw = function() {

	var overlayProjection = this.getProjection();
	var sw = overlayProjection.fromLatLngToDivPixel(this.pointLatlon_);
	
	var div = this.div_;
	div.style.left = sw.x-80 + 'px';
	div.style.bottom = -sw.y-80 + 'px';

}

WindOverlay.prototype.onRemove = function() {
	this.div_.parentNode.removeChild(this.div_);
}

	// Note that the visibility property must be a string enclosed in quotes
WindOverlay.prototype.hide = function() {
	if (this.div_) {
	  this.div_.style.visibility = "hidden";
	}
}

WindOverlay.prototype.show = function() {
	if (this.div_) {
	  this.div_.style.visibility = "visible";
	}
}

WindOverlay.prototype.toggle = function() {
	if (this.div_) {
	  if (this.div_.style.visibility == "hidden") {
		this.show();
	  } else {
		this.hide();
	  }
	}
}

WindOverlay.prototype.toggleDOM = function() {
	if (this.getMap()) {
	  this.setMap(null);
	} else {
	  this.setMap(this.map_);
	}
}

function drawWind(dc, posX, posY, value, direction)
{
	dc.DrawLine = function(x1,y1,x2,y2){
		this.moveTo(x1,y1);
		this.lineTo(x2,y2);
	}

	var pi = 3.14159265358979;

	function sind(d)
	{
		return Math.sin(d*pi/180);
	}
	function cosd(d)
	{
		return Math.cos(d*pi/180);
	}
	
	if(value > 1000 ) return;
    
    var l=40, s=10, w=20;
    var ax = posX+l*sind(direction),
    	   ay = posY-l*cosd(direction);
    
    dc.DrawLine(posX,posY,ax, ay);
    
    var rest = value+1;
    var n20=Math.floor(rest/20);
	
	console.log(n20);
    
    for(var i=0;i<n20;i++)
    {
    	var bx = ax - i*s*sind(direction),
    		   by = ay + i*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction),
    		   cy = by + w*sind(direction),
    		   
    		   dx = bx - s*sind(direction),
    		   dy = by + s*cosd(direction);
    		   
    	dc.DrawLine(bx,by,cx,cy);
    	dc.DrawLine(cx,cy,dx,dy);	
    }
    
    ax -= n20*s*sind(direction);
    ay += n20*s*cosd(direction);
    
    s = 8;
    rest -= n20*20;
    var n4 = Math.floor(rest/4);
    for(var i=0;i<n4;i++)
    {
    	var bx = ax - i*s*sind(direction),
    		   by = ay + i*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction),
    		   cy = by + w*sind(direction);
    		   
    	dc.DrawLine(bx,by,cx,cy);	
    }
    
    rest -= n4*4;
    
    if(rest >= 2 )
    {
    	var bx = ax - n4*s*sind(direction),
    		   by = ay + n4*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction)/2,
    		   cy = by + w*sind(direction)/2;
    		   
    	dc.DrawLine(bx,by,cx,cy);
    }
    
	dc.stroke();
    // Look at the wxDC docs to learn how to draw other stuff
}
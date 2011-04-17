//自定义层

RainOverlay.prototype = new google.maps.OverlayView();

function RainOverlay(map, swBound, text, stationId) {

	// Now initialize all properties.
	this.swBound_ = swBound;
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

	// Note: an overlay's receipt of add() indicates that
	// the map's panes are now available for attaching
	// the overlay to the map via the DOM.

	// Create the DIV and set some basic attributes.
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
		var cur = new Date();
		if(cur.getHours()>=20){
			cur.setDate(cur.getDate()+1);
		}
		
		function to2num(m){
			if(m<10) 
				return '0'+m;
			else
				return m;
		}
		
		var year = cur.getFullYear(), month = to2num(cur.getMonth()+1), day = cur.getDate();
		var stationId=$(this).attr('stationId');
		
		var url = 'http://www.hnaws.com/HNAWS/MSinfo/MSinfodisp.asp?Sel_TY='
					+year+'&Sel_TM='+month+'&Sel_TD='+day+'&StationNo='+stationId+'&StationName=Select Station';
		$('a.rain-table').attr('href',url);
		
		var scrollTop = $(document).scrollTop(),
			topValue = e.pageY-scrollTop-15;
		$('#moreinfo').css({left:e.pageX+'px',top:topValue+'px'}).show();
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
	var sw = overlayProjection.fromLatLngToDivPixel(this.swBound_);
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
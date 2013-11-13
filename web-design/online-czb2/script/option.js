var czbConfig = {};

czbConfig.stations = ['57070','57071','57073','57076','57066','57065','57074','57077','57162','57078'];
czbConfig.stationMap = {
	
		'57070':{ name:'新安',lon:'112.07',lat:'34.44',height:"364.0",highTdiff:0,lowTdiff:0 },
		'57071':{ name:'孟津',lon:'112.26',lat:'34.49',height:"333.3",highTdiff:0,lowTdiff:0 },
		
		'57073':{ name:'洛阳',lon:'112.25',lat:'34.40',height:"154.5",highTdiff:0,lowTdiff:0 },
		'57076':{ name:'偃师',lon:'112.49',lat:'34.43',height:"115.1",highTdiff:1,lowTdiff:0 },
		
		'57066':{ name:'洛宁',lon:'111.40',lat:'34.23',height:"328.3",highTdiff:0,lowTdiff:0 },
		'57065':{ name:'宜阳',lon:'112.11',lat:'34.30',height:"194.9",highTdiff:1,lowTdiff:1 },
		'57074':{ name:'伊川',lon:'112.25',lat:'34.25',height:"197.3",highTdiff:0,lowTdiff:-1 },
		
		'57077':{ name:'栾川',lon:'111.36',lat:'33.47',height:"750.3",highTdiff:-1,lowTdiff:-2 },
		'57162':{ name:'嵩县',lon:'112.05',lat:'34.09',height:"325.8",highTdiff:0,lowTdiff:0 },
		'57078':{ name:'汝阳',lon:'112.28',lat:'34.09',height:"336.5",highTdiff:0,lowTdiff:0 }
	};
	
czbConfig.defaultHighT = 25;
czbConfig.defaultLowT = 6;
	
czbConfig.cityCode = 'BFLB';
czbConfig.cityName = '洛阳市气象台';

czbConfig.isSendSingle = true;
czbConfig.singleCityId = '57073';
czbConfig.editMessageTime = ["205000","223500","022000","082000"];
czbConfig.forcastElements = 21;
czbConfig.possibleMaxPeriod = 168;

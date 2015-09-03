#include <pebble.h>
#include "Schedule.h"
  
static GameInfo Schedule1516[]={
  	{1442946600,"DAL","FLA"},	// DAL at FLA Sep 22, 2015 6:30
		{1443121200,"DAL","STL"},	// DAL at STL Sep 24, 2015 7:00
		{1443294000,"TB","DAL"},	// TB at DAL Sep 26, 2015 7:00
		{1443380400,"FLA","DAL"},	// FLA at DAL Sep 27, 2015 7:00
		{1443555000,"STL","DAL"},	// STL at DAL Sep 29, 2015 7:30
		{1443724200,"DAL","TB"},	// DAL at TB Oct 1, 2015 6:30
		{1443900600,"DAL","CHI"},	// DAL at CHI Oct 3, 2015 7:30
		{1444332600,"PIT","DAL"},	// PIT at DAL Oct 8, 2015 7:30
		{1444507200,"DAL","COL"},	// DAL at COL Oct 10, 2015 8:00
		{1444764600,"EDM","DAL"},	// EDM at DAL Oct 13, 2015 7:30
		{1444933800,"DAL","TB"},	// DAL at TB Oct 15, 2015 6:30
		{1445104800,"DAL","FLA"},	// DAL at FLA Oct 17, 2015 6:00
		{1445365800,"DAL","PHI"},	// DAL at PHI Oct 20, 2015 6:30
		{1445536800,"DAL","PIT"},	// DAL at PIT Oct 22, 2015 6:00
		{1445713200,"FLA","DAL"},	// FLA at DAL Oct 24, 2015 7:00
		{1445974200,"ANA","DAL"},	// ANA at DAL Oct 27, 2015 7:30
		{1446147000,"VAN","DAL"},	// VAN at DAL Oct 29, 2015 7:30
		{1446300000,"SJ","DAL"},	// SJ at DAL Oct 31, 2015 2:00
		{1446489000,"DAL","TOR"},	// DAL at TOR Nov 2, 2015 6:30
		{1446573600,"DAL","BOS"},	// DAL at BOS Nov 3, 2015 6:00
		{1446832800,"DAL","CAR"},	// DAL at CAR Nov 6, 2015 6:00
		{1446991200,"DAL","DET"},	// DAL at DET Nov 8, 2015 2:00
		{1447183800,"TOR","DAL"},	// TOR at DAL Nov 10, 2015 7:30
		{1447356600,"WIN","DAL"},	// WIN at DAL Nov 12, 2015 7:30
		{1447527600,"MIN","DAL"},	// MIN at DAL Nov 14, 2015 7:00
		{1447783200,"DAL","BUF"},	// DAL at BUF Nov 17, 2015 6:00
		{1447956000,"DAL","WAS"},	// DAL at WAS Nov 19, 2015 6:00
		{1448132400,"BUF","DAL"},	// BUF at DAL Nov 21, 2015 7:00
		{1448393400,"OTT","DAL"},	// OTT at DAL Nov 24, 2015 7:30
		{1448652600,"VAN","DAL"},	// VAN at DAL Nov 27, 2015 7:30
		{1448737200,"DAL","MIN"},	// DAL at MIN Nov 28, 2015 7:00
		{1449000000,"DAL","CGY"},	// DAL at CGY Dec 1, 2015 8:00
		{1449176400,"DAL","VAN"},	// DAL at VAN Dec 3, 2015 9:00
		{1449259200,"DAL","EDM"},	// DAL at EDM Dec 4, 2015 8:00
		{1449603000,"CAR","DAL"},	// CAR at DAL Dec 8, 2015 7:30
		{1449862200,"PHI","DAL"},	// PHI at DAL Dec 11, 2015 7:30
		{1449946800,"DAL","STL"},	// DAL at STL Dec 12, 2015 7:00
		{1450207800,"CBJ","DAL"},	// CBJ at DAL Dec 15, 2015 7:30
		{1450380600,"CGY","DAL"},	// CGY at DAL Dec 17, 2015 7:30
		{1450548000,"MTL","DAL"},	// MTL at DAL Dec 19, 2015 6:00
		{1450724400,"DAL","MIN"},	// DAL at MIN Dec 21, 2015 7:00
		{1450812600,"CHI","DAL"},	// CHI at DAL Dec 22, 2015 7:30
		{1451156400,"DAL","STL"},	// DAL at STL Dec 26, 2015 7:00
		{1451235600,"STL","DAL"},	// STL at DAL Dec 27, 2015 5:00
		{1451412000,"DAL","CBJ"},	// DAL at CBJ Dec 29, 2015 6:00
		{1451590200,"NSH","DAL"},	// NSH at DAL Dec 31, 2015 7:30
		{1451757600,"DAL","NJ"},	// DAL at NJ Jan 2, 2016 6:00
		{1451836800,"DAL","NYI"},	// DAL at NYI Jan 3, 2016 4:00
		{1452016800,"DAL","NYR"},	// DAL at NYR Jan 5, 2016 6:00
		{1452195000,"WIN","DAL"},	// WIN at DAL Jan 7, 2016 7:30
		{1452366000,"MIN","DAL"},	// MIN at DAL Jan 9, 2016 7:00
		{1452891600,"DAL","ANA"},	// DAL at ANA Jan 15, 2016 9:00
		{1452979800,"DAL","SJ"},	// DAL at SJ Jan 16, 2016 9:30
		{1453239000,"DAL","LA"},	// DAL at LA Jan 19, 2016 9:30
		{1453404600,"EDM","DAL"},	// EDM at DAL Jan 21, 2016 7:30
		{1453575600,"COL","DAL"},	// COL at DAL Jan 23, 2016 7:00
		{1453750200,"CGY","DAL"},	// CGY at DAL Jan 25, 2016 7:30
		{1454439600,"DAL","WIN"},	// DAL at WIN Feb 2, 2016 7:00
		{1454616000,"DAL","COL"},	// DAL at COL Feb 4, 2016 8:00
		{1454785200,"CHI","DAL"},	// CHI at DAL Feb 6, 2016 7:00
		{1455044400,"DAL","MIN"},	// DAL at MIN Feb 9, 2016 7:00
		{1455219000,"DAL","CHI"},	// DAL at CHI Feb 11, 2016 7:30
		{1455390000,"WAS","DAL"},	// WAS at DAL Feb 13, 2016 7:00
		{1455562800,"DAL","NSH"},	// DAL at NSH Feb 15, 2016 7:00
		{1455649200,"DAL","STL"},	// DAL at STL Feb 16, 2016 7:00
		{1455825600,"DAL","ARI"},	// DAL at ARI Feb 18, 2016 8:00
		{1455994800,"BOS","DAL"},	// BOS at DAL Feb 20, 2016 7:00
		{1456254000,"DAL","WIN"},	// DAL at WIN Feb 23, 2016 7:00
		{1456428600,"WIN","DAL"},	// WIN at DAL Feb 25, 2016 7:30
		{1456585200,"NYR","DAL"},	// NYR at DAL Feb 27, 2016 3:00
		{1456774200,"DET","DAL"},	// DET at DAL Feb 29, 2016 7:30
		{1456858800,"DAL","NSH"},	// DAL at NSH Mar 1, 2016 7:00
		{1457119800,"NJ","DAL"},	// NJ at DAL Mar 4, 2016 7:30
		{1457280000,"DAL","OTT"},	// DAL at OTT Mar 6, 2016 4:00
		{1457461800,"DAL","MTL"},	// DAL at MTL Mar 8, 2016 6:30
		{1457724600,"CHI","DAL"},	// CHI at DAL Mar 11, 2016 7:30
		{1457812800,"STL","DAL"},	// STL at DAL Mar 12, 2016 8:00
		{1458070200,"LA","DAL"},	// LA at DAL Mar 15, 2016 7:30
		{1458243000,"TB","DAL"},	// TB at DAL Mar 17, 2016 7:30
		{1458414000,"NYI","DAL"},	// NYI at DAL Mar 19, 2016 7:00
		{1458675000,"DAL","CHI"},	// DAL at CHI Mar 22, 2016 7:30
		{1458853200,"DAL","ARI"},	// DAL at ARI Mar 24, 2016 9:00
		{1459004400,"DAL","SJ"},	// DAL at SJ Mar 26, 2016 3:00
		{1459279800,"NSH","DAL"},	// NSH at DAL Mar 29, 2016 7:30
		{1459452600,"ARI","DAL"},	// ARI at DAL Mar 31, 2016 7:30
		{1459609200,"DAL","LA"},	// DAL at LA Apr 2, 2016 3:00
		{1459713600,"DAL","ANA"},	// DAL at ANA Apr 3, 2016 8:00
		{1460057400,"COL","DAL"},	// COL at DAL Apr 7, 2016 7:30
		{1460228400,"NSH","DAL"},	// NSH at DAL Apr 9, 2016 7:00
    {2000000000,"   ", "  "}, // end marker
};
static bool bToday = false;
// Check the schedule for the next game
GameInfo *FindGameTime()
{
  int nGame = 0;
  bToday = false;

  time_t now = time(NULL);
	struct tm *currentTime = gmtime(&now);
  while(Schedule1516[nGame].start < now){
    nGame++;
  }
	struct tm *startTime = gmtime(&Schedule1516[nGame].start);
  SetGameAlarm(startTime, Schedule1516[nGame].start, nGame);
  if((startTime->tm_mon == currentTime->tm_mon) && (startTime->tm_mday == currentTime->tm_mday)){
    bToday = true;
  }

  return &Schedule1516[nGame];
}
bool IsToday()
{
  return bToday;
}
static WakeupId wakeme;
static char s_StationStops[] = {
  4,	// T&P Station
  10,	// Ft. Worth Intermodal Center
  6,	// Richland Hills
  8,	// Bell
  5,	// CentrePort/ DFW Airport
  6,	// West Irving
  8,	// Downtown Irving/Heritage Crossing
  5,	// Medical/Market Center
};

static short s_SaturdayTrains[]={
  1242,  // 12:42
  1442,  // 2:42
  1612,  // 4:12
  1812,  // 6:12
  1912,  // 7:12
};
static short s_WeekDayTrains[] = {
  1904,  // 7:04
};
static void DoGameAlarm(WakeupId wakeup_id, int32_t cookie)
{
  // do a double vibrate
  // add the game window
}
void SetGameAlarm(struct tm *gameTime, time_t startTime, int32_t nGame)
{
  // make sure there are no pending wakeups
  wakeup_cancel_all();
  wakeup_service_subscribe(DoGameAlarm); 
  
  time_t when = startTime;
  switch(gameTime->tm_wday){
    case 0:  // Sunday, just use start time
    break;
    case 6:  // Saturday, search the train schedule
      when -= s_SaturdayTrains[0];
      // backup based on station stop
    break;
    default:  // Weekday schedule
      when -= s_WeekDayTrains[0];
    break;
  }

wakeme = wakeup_schedule(when, nGame, false);
  
  int x =  s_StationStops[0];
  x = s_SaturdayTrains[0];
  x = s_WeekDayTrains[0];
  if(!x){
    bToday = false;
  }
}

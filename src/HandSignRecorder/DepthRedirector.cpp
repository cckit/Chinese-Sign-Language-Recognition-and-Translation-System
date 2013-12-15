#include "Common.h"
#include <cstdio>
using namespace xn;

DepthGenerator g_depth;
MockDepthGenerator g_mockDepth;
Query mockDepthQuery;
extern UserGenerator g_user;

static XnMapOutputMode VGAMode = { 640, 480, 30 };
static XnUInt64 lastRecordTime = 0;
static DepthMetaData dmd;

static inline void recordMissedFrame(XnUInt64 &timeStamp){
	if(timeStamp-lastRecordTime > 35000*FRAME_PER_READ){
		int missed = (int)(timeStamp-lastRecordTime)/32000 - FRAME_PER_READ;
		//printf("Missed frame: %llu -> %llu = %d > %d - %d frames\n",
		//	lastRecordTime, timeStamp, XnUInt32(timeStamp-lastRecordTime), 35000*FRAME_PER_READ, missed);
	}
}

bool updateDepthData(Context &context){
	static XnUInt64 timeStamp;

	g_depth.WaitAndUpdateData();
	timeStamp = g_depth.GetTimestamp();
	
	if(timeStamp-lastRecordTime > 35000*(FRAME_PER_READ-1)){
		g_depth.GetMetaData(dmd);
		g_mockDepth.SetData(dmd);
		g_user.WaitAndUpdateData();
		recordMissedFrame(timeStamp);
		lastRecordTime = timeStamp;

		return true;
	}else{
		recordMissedFrame(timeStamp);
		return false;
	}
	
}

void setDepthEvents(Context &context){
	// Actual Depth Generator
	assertOK("Create Depth", g_depth.Create(context));
	g_depth.SetMapOutputMode(VGAMode);
	g_depth.GetMirrorCap().SetMirror(TRUE);
	g_depth.SetIntProperty("HoleFilter", TRUE);

	// Mock Depth Generator
	assertOK("Create Depth", g_mockDepth.CreateBasedOn(g_depth, "mock-depth"));
	assertOK("Add Needed Node", mockDepthQuery.AddNeededNode("mock-depth"));
}


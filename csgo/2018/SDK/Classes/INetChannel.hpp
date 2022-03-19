#pragma once
#include "IVEngineClient.hpp"
#include "Exploits.hpp"
#include "../Valve/netadr.h"

#define MAX_FLOWS 2
#define MAX_STREAMS 2
#define MAX_SUBCHANNELS		8		// we have 8 alternative send&wait bits
#define SUBCHANNEL_FREE		0	// subchannel is free to use
#define SUBCHANNEL_TOSEND	1	// subchannel has data, but not send yet
#define SUBCHANNEL_WAITING	2   // sbuchannel sent data, waiting for ACK
#define SUBCHANNEL_DIRTY	3	// subchannel is marked as dirty during changelevel

#define FRAGMENT_BITS		8
#define FRAGMENT_SIZE		(1<<FRAGMENT_BITS)
#define BYTES2FRAGMENTS(i) ((i+FRAGMENT_SIZE-1)/FRAGMENT_SIZE)
#define NET_MAX_PAYLOAD_BITS 19
#define MAX_FILE_SIZE_BITS 26
#define MAX_FILE_SIZE		((1<<MAX_FILE_SIZE_BITS)-1)	// maximum transferable size is	64MB

#define	FRAG_NORMAL_STREAM	0
#define FRAG_FILE_STREAM	1

#define Bits2Bytes(b) ((b+7)>>3)

class INetChannel;

class INetChannelHandler
{
public:
	virtual	~INetChannelHandler(void) {};

	virtual void ConnectionStart(INetChannel* chan) = 0;	// called first time network channel is established

	virtual void ConnectionClosing(const char* reason) = 0; // network channel is being closed by remote site

	virtual void ConnectionCrashed(const char* reason) = 0; // network error occured

	virtual void PacketStart(int incoming_sequence, int outgoing_acknowledged) = 0;	// called each time a new packet arrived

	virtual void PacketEnd(void) = 0; // all messages has been parsed

	virtual void FileRequested(const char* fileName, unsigned int transferID) = 0; // other side request a file for download

	virtual void FileReceived(const char* fileName, unsigned int transferID) = 0; // we received a file

	virtual void FileDenied(const char* fileName, unsigned int transferID) = 0;	// a file request was denied by other side

	virtual void FileSent(const char* fileName, unsigned int transferID) = 0;	// we sent a file
};

class INetChannelInfo
{
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char* GetName(void) const = 0;	// get channel name
	virtual const char* GetAddress(void) const = 0; // get channel IP address as string
	virtual float		GetTime(void) const = 0;	// current net time
	virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
	virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut(void) const = 0;	// true if timing out
	virtual bool		IsPlayback(void) const = 0;	// true if demo playback

	virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		GetStreamProgress(int flow, int* received, int* total) const = 0;  // TCP progress if transmitting
	virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};

#pragma pack(push, 1)
struct netframe_t_firstpart
{
	float time; //0
	int size; //4
	__int16 choked; //8
	bool valid; //10
	char pad; //11
	float latency; //12
};
#pragma pack(pop)

#pragma pack(push, 1)
struct netframe_t_secondpart
{
	int dropped; //16
	float avg_latency;
	float m_flInterpolationAmount;
	unsigned __int16 msggroups[16];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct netflow_t
{
	float nextcompute; //0
	float avgbytespersec; //4
	float avgpacketspersec; //8
	float avgloss; //12
	float avgchoke; //16
	float avglatency; //20
	float latency; //24
	int totalpackets; //28
	int totalbytes; //32
	int currentindex; //36
	netframe_t_firstpart frames[128]; //40
	netframe_t_secondpart frames2[128]; //2088
	netframe_t_firstpart* currentframe; //7720
};
#pragma pack(pop)

class INetChannel {
public:
	virtual float GetTime();
	virtual float GetTimeConnected();
	virtual float GetTimeSinceLastReceived();
	virtual int GetDataRate();
	virtual int GetBufferSize();
	virtual bool IsLoopback();
	virtual bool IsNull();
	virtual bool IsTimingOut();
	virtual bool IsPlayback();
	virtual float GetLatency(int flow);
	virtual float GetAvgLatency(int flow);
	virtual float GetAvgLoss(int flow);
	virtual float GetAvgData(int flow);
	virtual float GetAvgChoke(int flow);
	virtual float GetAvgPackets(int flow);
	virtual int GetTotalData(int flow);
	virtual int GetSequenceNr(int flow);
	virtual bool IsValidPacket(int flow, int frame_number);
	virtual float GetPacketTime(int flow, int frame_number);
	virtual int	GetPacketBytes(int flow, int frame_number, int group);
	virtual bool GetStreamProgress(int flow, int* received, int* total);
	virtual float GetCommandInterpolationAmount(int flow, int frame_number);
	virtual void GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke);
	virtual void GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDeviation);
	virtual float GetTimeoutSeconds();

	//char pad_0000[16];           //0x0004
	//bool m_bProcessingMessages;  //0x0014
	//bool m_bShouldDelete;        //0x0015
	//char pad_0016[2];            //0x0016
	//int32_t m_nOutSequenceNr;    //0x0018 last send outgoing sequence number
	//int32_t m_nInSequenceNr;     //0x001C last received incoming sequnec number
	//int32_t m_nOutSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
	//int32_t m_nOutReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
	//int32_t m_nInReliableState;  //0x0028 state of incoming reliable data
	//int32_t m_nChokedPackets;    //0x002C number of choked packets
	//char pad_0030[1044];         //0x0030
	__int32 vtable; //0x0000 
	void* spacer1; //0x0004 
	void* spacer2; //0x0008 
	void* spacer3; //0x000C 
	void* spacer4; //0x0010 
	unsigned char m_bProcessingMessages; //0x0014 
	unsigned char m_bShouldDelete; //0x0015 
	char pad_0x0016[0x2]; //0x0016
	__int32 m_nOutSequenceNr; //0x0018 
	__int32 m_nInSequenceNr; //0x001C 
	__int32 m_nOutSequenceNrAck; //0x0020 
	__int32 m_nOutReliableState; //0x0024 
	__int32 m_nInReliableState; //0x0028 
	__int32 m_nChokedPackets; //0x002C 

	bf_write m_StreamReliable; //0x0030 
	/*CUtlMemory*/ char m_ReliableDataBuffer[12]; //0x0048 
	bf_write m_StreamUnreliable; //0x0054 
	/*CUtlMemory*/ char m_UnreliableDataBuffer[12]; //0x006C 
	bf_write m_StreamVoice; //0x0078 
	/*CUtlMemory*/char m_VoiceDataBuffer[12]; //0x0090 
	__int32 m_Socket; //0x009C 
	__int32 m_StreamSocket; //0x00A0 
	__int32 m_MaxReliablePayloadSize; //0x00A4 
	char pad_0x00A8[0x4]; //0x00A8
	netadr_t remote_address; //0x00AC 
	char dylanpadding[84]; //padding added by dylan
	float last_received; //0x00B8  //dylan found 0x10c
	//char pad_0x00BC[0x4]; //0x00BC
	double /*float*/ connect_time; //0x00C0 //dylan found 0x110
	//char pad_0x00C4[0x4]; //0x00C4
	__int32 m_Rate; //0x00C8  //dylan found 0x118
	/*float*/double m_fClearTime; //0x00CC  //dylan found 0x120
	char pad_0x00D0[0x8]; //0x00D0
	char m_WaitingList[48];
	////CUtlVector m_WaitingList[0]; //0x00D8 
	////CUtlVector m_WaitingList[1]; //0x00EC 
	////char pad_0x0100[0x4120]; //0x0100
	////char pad_0x0100[0x40F0]; //dylan changed
	//__int32 m_PacketDrop; //0x4220  //dylan found 0x4250
	//char m_Name[32]; //0x4224 
	//__int32 m_ChallengeNr; //0x4244 
	//float m_Timeout; //0x4248 //dylan found 0x4278
	//INetChannelHandler* m_MessageHandler; //0x424C 
	///*CUtlVector*/char m_NetMessages[14]; //0x4250 
	//__int32 dylanUnknown;
	//void* m_pDemoRecorder; //0x4264 
	//__int32 m_nQueuedPackets; //0x4268  //dylan found 0x4298
	//float m_flInterpolationAmount; //0x426C //dylan found 0x429c
	//float m_flRemoteFrameTime; //0x4270 //dylan found 0x42a0
	//float m_flRemoteFrameTimeStdDeviation; //0x4274  //dylan found 0x42a4
	//float m_flRemoteFrameTimeUnknown; //dylan found 0x42a8
	//__int32 m_nMaxRoutablePayloadSize; //0x4278  //dylan found 0x42ac
	//__int32 m_nSplitPacketSequence; //0x427C  //dylan found 0x42b0
	//char pad_0x4280[0x14]; //0x4280

	//char NEWPAD2018[4];
	//#endif
	netflow_t m_DataFlow[MAX_FLOWS]; //new 2018 0x49C //0x5C0
	int	m_MsgStats[16];	// total bytes for each message group
	__int32 m_PacketDrop; //0x4220  //dylan found 0x4250 new 0x4258 newnew 0x425C
	//char m_UnkPad[4];
	char m_Name[32]; //0x4224 
	__int32 m_ChallengeNr; //0x4244 
	float m_Timeout; //0x4280
	INetChannelHandler* m_MessageHandler; //0x4284   0x4288
	/*CUtlVector*/char m_NetMessages[16]; //dylan found 0x4284
	__int32 dylanUnknown;
	void* m_pDemoRecorder; //0x429C
	//__int32 dylanUnknown923874;
	//__int32 m_nQueuedPackets; //0x4268  //dylan found 0x4298
	float m_flInterpolationAmount; //0x42A0
	double m_flRemoteFrameTime; //0x42A4
	float m_flRemoteFrameTimeStdDeviation; //0x42AC
	__int32 m_nMaxRoutablePayloadSize; //0x42B0
	__int32 m_nSplitPacketSequence; //dylan found 0x42b4
	char pad_0x4280[0x14]; //0x4280

	int SendDatagram(uintptr_t* datagram = nullptr) {
		return Memory::VCall< bool(__thiscall*)(void*, uintptr_t*) >(this, 48)(this, datagram);
	}
}; //Size: 0x4294

extern INetChannel our_netchan;
extern INetChannel server_netchan;
extern INetChannel client_netchan;

extern void UpdateCustomNetChannels();
void FlowNewPacket(INetChannel* chan, int flow, int seqnr, int acknr, int nChoked, int nDropped, int nSize);
void FlowUpdate(INetChannel* chan, int flow, int addbytes);
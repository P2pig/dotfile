#define NotFound -1
#define LS	1
#define PWD	2
#define CD	3
#define GET	4

#define LLS	5
#define LPWD	6
#define LCD	7
#define PUT	8

#define QUIT   9

struct Msg
{
	char cmd[512];
	int type;
	char buffer[1024];

};

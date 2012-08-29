/*
 *  ELSSaveFile.cpp
 *  GameBox
 *
 *  Created by xing zip on 11-2-17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "AnimationLayerPlayELS.h"
#include "ELSSaveData.h"
#include "GameLayerPlayELS.h"
#define MAXRECACT (8192*3)	
static RECACT g_recact[MAXRECACT];
static FILE  *g_rep;

//纪录动作，用于replay
void GameLayerPlayELS::RecordAction(int idx, const char *act)
{
	if(GameSet->gamemode == ELS_MODE_REPLAY) return;
	/*if (GameSet->gamemode == ELS_MODE_NET) 
	{
		if (idx==0 && !isRobotGame())
		{
			//g_net_send++;
			//printf("NETSEND...%d...blockidx=%d...act=%s\n", g_net_send, mGS[0].block_index, act);
			//netSend("action:D");
			NetSend(act);
		}
	}*/
	if(g_recact_count>=MAXRECACT)
	{
		printf("TOO MUCH ACTION\n");
		return;
	}
	RECACT *ra=&g_recact[g_recact_count];
	ra->idx=idx;
	snprintf(ra->act, 16, "%s", act);
	ra->stage=mStage;
	g_recact_count++;
}

//保存replay文件
 void GameLayerPlayELS::SaveAction()
{
	if (mRepSaved) 
		return;
	else 
		mRepSaved=1;
	
	char fn[64];
	int ct=time(NULL);
	sprintf(fn, "%d.rep", ct);
	if (g_mvRepFiles.size()>=MAX_REP_COUNT) {
		int lastidx=g_mvRepFiles.size()-1;
		printf("delete the oldest rep...%d\n", g_mvRepFiles[lastidx]);
		char ulfn[64];
		sprintf(ulfn, "%d.rep", g_mvRepFiles[lastidx]);
		const char *ulpath=GetDocPath(ulfn, NULL);
		unlink(ulpath);
		g_mvRepFiles.erase(g_mvRepFiles.end()-1);
	}
	g_mvRepFiles.insert(g_mvRepFiles.begin(), ct);

	const char *path = GetDocPath(fn, NULL);
	if((g_rep=fopen(path,"rb+"))==NULL)
	{
		if((g_rep=fopen(path, "wb+"))==NULL)
			return;
	}
	//fseek(g_rep, 0, SEEK_END);
	//printf("cur file point=%ld\n", ftell(g_rep));
	unsigned int mode=mBJIdx*10000+GameSet->gamemode*1000+mTheme*100+mNanDu*10;
	fseek(g_rep, 0, SEEK_SET);
	for (int i=0; i<4; i++) 
		fwrite(&g_seats[i], sizeof(ELSUSER), 1, g_rep);
    fprintf(g_rep, "%u %u %d %d %d %d %d %d\n", mRandomSeed, mode, g_seatId, 
			g_xunzhang4saverep[0], g_xunzhang4saverep[1], g_xunzhang4saverep[2],
			g_xunzhang4saverep[3], g_xunzhang4saverep[4]);
	printf("mode=%d\n", mode);
	for(int i=0;i<g_recact_count;i++)
		fprintf(g_rep, "%d %d %s\n", g_recact[i].idx, g_recact[i].stage, g_recact[i].act);
	fflush(g_rep);
	fclose(g_rep);
}

//载入replay文件
/*
void GameStatePlay::LoadAction(const char *fn)
{
	unsigned int mode=0;
	const char *path;
	printf(".....%s\n", fn);
	if (strcmp(fn, "demo.rep"))
		path = GetDocPath(fn, NULL);
	else 
		path = GetPath("demo.rep", NULL);
	printf("replay path=%s\n", path);
	if((g_rep=fopen(path,"r"))==NULL)
	{
		if((g_rep=fopen(path, "wb+"))==NULL)
			return;
	}
	fseek(g_rep, 0, SEEK_END);
	printf("cur file(%s) size=%ld\n", fn, ftell(g_rep));
	fseek(g_rep, 0, SEEK_SET);
	g_robot=0;
	for (int i=0; i<4; i++) 
	{
		fread(&g_seats[i], sizeof(ELSUSER), 1, g_rep);
		if (g_seats[i].isrobot) {
			g_robot=1;
		}
	}
	fscanf(g_rep, "%u %u %d %d %d %d %d %d\n", &mRandomSeed, &mode, &g_seatId,
		   &g_xunzhang[0], &g_xunzhang[1], &g_xunzhang[2],
		   &g_xunzhang[3], &g_xunzhang[4]);
	mBJIdx   = mode/10000;			
	mElsRepMode = mode/1000%10;
	mTheme   = mode/100%10;
	mNanDu   = mode/10%10;
	printf("mode=%d\n", mode);
	g_recact_count=0;
	for(;;)
	{
		int  idx, stage;
		char act[16];
		int ret=fscanf(g_rep, "%d %d %s\n", &idx, &stage, act);
		g_recact[g_recact_count].idx=idx;
		g_recact[g_recact_count].stage=stage;
		snprintf(g_recact[g_recact_count].act,16,"%s",act);
		if(ret==3)
			g_recact_count++;
		else 
			break;
	}
	fclose(g_rep);
	g_recact_index=0;
}

//回放动作
void GameStatePlay::PlayReplayAction()
{
	int stage, index;
	char act[16];
	
	index=g_recact[g_recact_index].idx;
	stage=g_recact[g_recact_index].stage;
	snprintf(act, 16, "%s", g_recact[g_recact_index].act);
	//printf("REP:%d %d %s mstage=%d g_recact_index=%d\n", index, stage, act, mStage, g_recact_index);
	
	while (mStage==(stage+1)) {
		g_recact_index++;
		//printf("REP:%d %d %s mstage=%d g_recact_index=%d\n", index, stage, act, mStage, g_recact_index);
		PlayActionBase(act, index);
		//do action
		index=g_recact[g_recact_index].idx;
		stage=g_recact[g_recact_index].stage;
		snprintf(act, 16, "%s", g_recact[g_recact_index].act);
	}
}

void GameStatePlay::ReadOption()
{
	const char *fn = "game.conf";
	const char *path = GetDocPath(fn, NULL);
	FILE *fp;
	
	if((fp=fopen(path, "r"))==NULL)
	{
		g_options[0]=1;
		g_options[1]=1;
		g_options[2]=0;
		g_options[3]=0;
		g_options[4]=1;
		g_options[5]=0;
		g_options[6]=0;
		g_options[7]=1;//是否初次进入游戏，判断是否显示帮助
		g_options[8]=5;//再次显示道具帮助的次数，每显示都减一。
		g_options[9]=5;//再次显示hold帮助的次数。
	}
	else
	{
		fscanf(fp, "%d %d %d %d %d %d %d %d %d %d", &g_options[0], &g_options[1], &g_options[2], 
		   &g_options[3], &g_options[4], &g_options[5], &g_options[6], &g_options[7], &g_options[8], &g_options[9]);
		fclose(fp);
	}
	
	//For debug,open all map...
	//g_options[5]=1;
	//printf("UNLOCK ALL MAPS.................\n");
	
	//init robot name...
	const char *pathrobot;
	int rcount=0;
	pathrobot = GetPath("name.txt", NULL);
	printf("ROBOTNAME=%s\n", pathrobot);
	if((fp=fopen(pathrobot, "r"))!=NULL)
	{
		while (1) {
			int ret=fscanf(fp, "%s", g_robotname[rcount]);
			if(ret!=1) break;
			rcount++;
		}
		printf("ROBOT COUNT=%d\n", rcount);
		fclose(fp);
	}
}

void GameStatePlay::WriteOption()
{
	FILE *fp;
	
	const char *fn = "game.conf";
	const char *path = GetDocPath(fn, NULL);
	
	if((fp=fopen(path,"rb+"))==NULL)
	{
		if((fp=fopen(path, "wb+"))==NULL)
			return;
	}
	
	fprintf(fp, "%d %d %d %d %d %d %d %d %d %d", g_options[0], g_options[1], g_options[2], 
			g_options[3], g_options[4], g_options[5], g_options[6], g_options[7], g_options[8], g_options[9]);
	fclose(fp);
}

//读取存盘文件
void GameStatePlay::ReadScore()
{
	const char *fn = "game.save";
	const char *path = GetDocPath(fn, NULL);
	FILE *fp;
	int count;
	
	if((fp=fopen(path, "r"))==NULL)
		return;
	
	printf("Read score from %s\n", path);
	
	//读取分数
	fscanf(fp, "%d", &count);
	if(count<0 || count>10)
	{
		fclose(fp);
		return;
	}
	g_mvHS.clear();
	for(int j=0;j<count;j++)
	{
		HSCORE *phs = new HSCORE;
		fscanf(fp, "%d %d %d %s", 
		&phs->score, &phs->hang, 
		&phs->combo, phs->date);
		phs->is_current=false;
		g_mvHS.push_back(phs);
	}
		
	//读取勋章
	int ret     = fscanf(fp, "%d %d %d %d %d", 
					 &g_xunzhang[0], &g_xunzhang[1], &g_xunzhang[2],
					 &g_xunzhang[3], &g_xunzhang[4]);
	if (ret!=5) 
		memset(g_xunzhang, 0, 5*sizeof(int));
	
	ret     = fscanf(fp, "%d\n", &g_unlock_bmp);
	
	if (ret!=1) 
		g_unlock_bmp=1;
	
	//For debug...
	//g_unlock_bmp=40;
	
	//adventure里每关所得的星星
	for (int j=0; j<MAX_BMP_COUNT; j++) {
		ret = fscanf(fp, "%d ", &g_star_bmp[j]);
		if (ret!=1)
			g_star_bmp[j]=0;
	}
	
	fclose(fp);
}

//写入分数文件
void GameStatePlay::WriteScore()
{
	FILE *fp;
	
	const char *fn = "game.save";
	const char *path = GetDocPath(fn, NULL);
	
	if((fp=fopen(path,"rb+"))==NULL)
	{
		if((fp=fopen(path, "wb+"))==NULL)
			return;
	}

	printf("write score to %s...\n", path);
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%d\n", (int)g_mvHS.size());
	for(int i=0;i<g_mvHS.size();i++)
		fprintf(fp, "%d %d %d %s\n", 
				g_mvHS[i]->score,g_mvHS[i]->hang,
				g_mvHS[i]->combo,g_mvHS[i]->date);
	
	fprintf(fp, "%d %d %d %d %d\n", 
			g_xunzhang[0], g_xunzhang[1], g_xunzhang[2],
			g_xunzhang[3], g_xunzhang[4]);
	
	fprintf(fp, "%d\n", g_unlock_bmp);
	for (int i=0; i<MAX_BMP_COUNT; i++) {
		fprintf(fp, "%d ", g_star_bmp[i]);//g_star_bmp[i]只有在取得了比之前的记录更高的星星时才会变，所以这样赋值应该没问题
	}
	fclose(fp);
}

void GameStatePlay::SetXunZhang(int n)
{
	if (g_xunzhang[n]==0) {
		printf("Set xunzhang %d\n", n);
		g_xunzhang[n]=1;
		//mGS[0].xunzhang_stage=MAX_XUNZHANG_STAGE;
		mGS[0].xunzhang_trigger=n;
		WriteScore();
	}
}
*/

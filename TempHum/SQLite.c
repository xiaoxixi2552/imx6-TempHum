#include "SQLite.h"
/**
**
** @auther lyj_uptech@126.com
** @date 2007-3-21
** //�������ṩ�˶����ݿ���в����Ļ����ӿڣ����ڸ����ӵĲ������û����Ը��ݾ������
**   �����޸ģ�����ĸ��£��Լ�������������ϵ���˻��߼���֧��
**   
**   �������������Ψһ�ԡ��û������ʵ���ӹ��ܣ�
**
**   ���ڿ��Է�������table�Ķ�̬sql�����Բο����еĳ���ʵ�֣�
**/
sqlite3 *db;//ȫ�ֵ���������

//�û���һ�δ����ݿ�ʱӦ������Ӧ��table������ʵ������ݼ�¼

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
/**
* 
*���������ݿ������
* 
*
*/
int sqliteDB_open(){

	int rc;//������־
	printf("\ncreat database:test.db\n\ncreat table:table merchandise(contents:id name price)\n\nand add two records\n");
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	printf("\nOpen sucess!");

	if(!sqliteDB_create_table())
		printf("\ntable exist");
/*
	if(!sqliteDB_insert_records())
		printf("\ninsert table faild");
  else sqliteDB_opt_select_all();
*/
	return 1;
}
/**
*
* �ر������ݿ������ 
*
*/
int sqliteDB_close(){
	if(db != 0)  
		sqlite3_close(db);
}
/**
*
* ���һ����¼����֪��δ֪���ݿ��
*
*/
int sqliteDB_opt_add(char *time,int tem,int hum){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="insert into merchandise values('";

// by sprife for mem out

	char tem_sql0[5] = "','";
      	char tem_sql1[5] = "',";
      	char tem_sql2[5] = ");";
	char temperature[20];
	char humidity[20];

	sprintf(temperature, " %d" , tem);//��int����ת��Ϊ�ַ���
        sprintf(humidity, " %d" , hum);
	sql = strcat(tem_sql,time);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,temperature);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,humidity);
	sql = strcat(sql,tem_sql2);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**
*
* ɾ�����е�һ����¼
* @param name
*/
int sqliteDB_opt_delete(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="delete from merchandise where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//ɾ��֮ǰ��ѯ������¼�����������ʾ�ü�¼����ѯ���Ƿ����Ҫɾ��
	                        //�粻�������Ƴ����β���

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**
*
* ɾ�����е�һ����¼
* @param id
*/
int sqliteDB_opt_delete_by_id(char *id){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="delete from merchandise where id = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//ɾ��֮ǰ��ѯ������¼�����������ʾ�ü�¼����ѯ���Ƿ����Ҫɾ��
	                        //�粻�������Ƴ����β���

	sql = strcat(tem_sql,id);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/*******************************************************
******************************************************/
/**
*
* �޸����ݿ���еļ�¼����
* //�ݲ��ṩ�޸ĺ���2007-3-21
*/
int sqliteDB_opt_modify();
/**
*
* ��Ԥ�����sql������sql���ķ���ʱ��
* 
* ֻ���� ��ѯ���
* @2007-3-22
* ��ѯ���
*/
int sqliteDB_opt_select_all(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *name,*id;
 	int price=0;
 	int nret=sqlite3_prepare(db,"SELECT * FROM merchandise;",strlen("SELECT * FROM merchandise;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return false;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		name=sqlite3_column_text(stmt,0);
  		id=sqlite3_column_text(stmt,1);
  		price=sqlite3_column_int(stmt,2);
  		printf("\t%s\t\t%s\t\t%d\n",name,id,price);
 	}

 	sqlite3_finalize(stmt);
 	printf("\n");
 	return true;
}
/**
* ��ѯ���ϲ�ѯ�����ļ�¼
* @param name
*/
int sqliteDB_opt_select(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_id;
 	int price=0;
 	int nret=0;
	int rc;
	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="select * from merchandise where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		_name=sqlite3_column_text(stmt,0);
  		_id=sqlite3_column_text(stmt,1);
  		price=sqlite3_column_int(stmt,2);
  		printf("\t%s\t\t%s\t\t%d\n",_name,_id,price);
 	}
	
	sqlite3_finalize(stmt);
	printf("\n");
	return true;
}
/**
* ��ѯ���ϲ�ѯ�����ļ�¼
* @param id
*/
int sqliteDB_opt_select_by_id(char *id){
	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_id;
 	int price=0;
 	int nret=0;
	int rc;
	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="select * from merchandise where id = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,id);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");

 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		_name=sqlite3_column_text(stmt,0);
  		_id=sqlite3_column_text(stmt,1);
  		price=sqlite3_column_int(stmt,2);
  		printf("\t%s\t\t%s\t\t%d\n",_name,_id,price);
 	}

	sqlite3_finalize(stmt);
	printf("\n");
	return true;
}
/**
**
**
**�ڲ����ú���
**
**/
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  	int i;
  	for(i=0; i<argc; i++){
    		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  	}

  	printf("\n");
  	return 0;
}
/**
**
**�ڲ����ú���
**�����ж�����ѯ�ļ�¼�Ƿ����
** ���ݣ���Ʒ��
**/
int sqliteDB_exist(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name;
 	int price=0;
 	int nret=0;
	int rc;

	char *sql=0;//��̬���ɵ�SQL���
	char tem_sql[256]="select * from merchandise where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	printf("sql: %s",sql);
	if(nret!=SQLITE_OK)
		return false;
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		printf("\n this record does not exist!!");
		return false;
	}
	
	sqlite3_finalize(stmt);
	return true;
}
/**
**
**���û���û�д���tableʱ���øú�������һ��table
**
**/
int sqliteDB_create_table(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE merchandise(time varchar(40),temperature smallint,humidity smallint);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else

  	return true;
}
/**
**
**��ʼ�����ݿ�tableʱԤ������������
**
**/
int sqliteDB_insert_records()
{
 	char* zErrMsg=NULL;
 	char sql1[256]="INSERT INTO merchandise VALUES('ibm','277325073',483);";
 	char sql2[256]="INSERT INTO merchandise VALUES('sun','433443',400);";

 	int nret=sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);

 	nret=sqlite3_exec(db,sql2,NULL,NULL,&zErrMsg);
 	if(nret!=SQLITE_OK){
 	 	printf("%s\n",sqlite3_errmsg(db));
  		return false;
 	}
 	else
  	return true;
}

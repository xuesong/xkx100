// /d/xiakedao/road3.c ���͵� ɽ·3

inherit ROOM;
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
����ͨ��ɽ����С·��·���Ӳݴ�����������һЩ��֪����Ұ
�������ܾ����ĵ�û����������������������һ��ɽҰ�ķҷ�ֱ��
���顣
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "northdown" : __DIR__"road2",
                "southup" : __DIR__"road4",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -3000);
	set("coor/y", -22040);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}
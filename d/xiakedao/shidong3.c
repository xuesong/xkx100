// Room: /xiakedao/shidong3.c

inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ��ʯ�������ܵ��Ű�յ�͵ƣ�ʹ����������ǳ�������
ɽ����֧·���࣬���ҪС�ģ����ߴ���·��
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __DIR__"shidong4",
                "north" : __DIR__"yingbin",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -3070);
	set("coor/y", -22090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
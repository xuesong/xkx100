#include <ansi.h>
inherit __DIR__"pill";

void create()
{//2.  ������֥	HIG	30000		15000	5		���ڸ�ɽ�ϵ����ҩ�ģ����ú�������ڹ��ȼ���

        set_name(HIG "������֥" NOR, ({ "bainian lingzhi", "lingzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
								set("long", HIG "���ڸ�ɽ�ϵ����ҩ�ģ����ú�������ڹ��ȼ���\n" NOR);
								set("unit", "��");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 30000);
                set("force_point", 5);
                set("pill_msg1", HIR "��ֻ��һ��ů��ɢ��ȫ����˵������������á�\n" NOR);
                set("pill_msg2", HIY "��ֻ��һ������ӿ�ϣ���Ϣ�õ�����ȫ�Ĳ��䡣\n" NOR);
        }
        setup();
}
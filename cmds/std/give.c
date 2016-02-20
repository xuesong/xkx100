// /cmds/std/give.c

// Modified by Constant Jan 5 2001
// Modified by Zeratul Jan 12 2001
inherit F_CLEAN_UP;

#include <ansi.h>

int do_give(object me, object obj, object who);
object i_have(object env,string name); // env��ȡ���� name����Ʒ
string filter_color(string arg);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string target, item;
	object obj, who, *inv, obj2;
	int i, amount;

	if(!arg) return notify_fail("��Ҫ��˭ʲô������\n");
	if( me->is_busy() ) return notify_fail("����һ��������û����ɣ�\n");
	if( sscanf(arg, "%s to %s", item, target)==2 ||
		sscanf(arg, "%s %s", target, item)==2 );
	else return notify_fail("��Ҫ��˭ʲô������\n");
//	if(!objectp(who = present(target, environment(me))) ||
	if(!objectp(who = i_have( environment(me),target )) ||
		!living(who) || who->query_temp("noliving") )
		return notify_fail("����û��������ˡ�\n");
	if( who->query("env/no_accept") )
		return notify_fail("�˼����ڲ���Ҫʲô������\n");
	if(sscanf(item, "%d %s", amount, item)==2)
	{
	//	if( !objectp(obj = present(item, me)) )	
		if( !objectp(obj = i_have( me,item )) ) // me have item	
			return notify_fail("������û������������\n");
		if( obj->query("no_drop") )
			return notify_fail("�����������������ˡ�\n");
		if( !obj->query_amount() )	
			return notify_fail( obj->name() + "���ܱ��ֿ����ˡ�\n");
		if( amount < 1 )
			return notify_fail("����������������һ����\n");
		if( amount > obj->query_amount() ) 
			return notify_fail("��û����ô���"+obj->name()+"��\n");
		else if( amount == (int)obj->query_amount() )
			return do_give(me, obj, who);
		else
		{
			obj->set_amount( (int)obj->query_amount() - amount );
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			if (do_give(me, obj2, who)) return 1;
			else
			{
				obj->set_amount((int)obj->query_amount() + amount);
				return 0;
			}
		}
	}
	if(arg=="all")
	{
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++)
		{
			do_give(me, inv[i], who);
		}
		write("�����ˡ�\n");
		return 1;
	}
//	if(!objectp(obj = present(item, me)))
	if(!objectp(obj = i_have( me,item)))
		return notify_fail("������û������������\n");
	return do_give(me, obj, who);
}

int do_give(object me, object obj, object who)
{

	if( obj->query("no_drop") )
		return notify_fail("�����������������ˡ�\n");
	if( obj->query_temp("is_rided_by") )
		return notify_fail("����������ˣ��㲻�͵������ˣ�\n");
	if( userp(obj) )
		return notify_fail("��ֻ������ҡ�\n");
	// ���Ӷ�������Ʒ�������жϡ�
	// Added by Constant Jan 5 2001
	if (obj->query("owner") != me->query("id") && (obj->query("taskobj")))
		return notify_fail("��������Լ���ɡ�\n");
	if (obj->query("dynamic_quest") && TASK_D->quest_reward(me, who, obj))
		return 1;
	if ((strsrch(obj->query("name"), me->query("quest/betrayer/name")) >= 0)
		&& who->accept_quest_betrayer(me, obj))
		return 1;
	if ((strsrch(obj->query("name"), me->query("quest/book/book")) >= 0)
		&& who->accept_quest_book(me, obj))
		return 1;
	if ((strsrch(obj->query("name"), me->query("quest/thief/name")) >= 0)
		&& who->accept_quest_thief(me, obj))
		return 1;
	if ((strsrch(obj->query("name"), me->query("quest/kill/name")) >= 0)
		&& who->accept_quest_kill(me, obj))
		return 1;
	if( !interactive(who) && !who->accept_object(me, obj) )
		return notify_fail("�Է������������������\n");
	if (!objectp(obj)) return 1;
	if (obj->query("id") == "bao wu")
	{
		destruct(obj);
		return 1;
	}
// �����Ͷ��״
	if( obj->query("id") == "head")
		who->set_temp("party/toumingzhuang", me->query("id"));
	if( !userp(who) && obj->value() )
	{
		message_vision("$N�ó�" + obj->short() + "��$n��\n", me, who);
		destruct(obj);
        	me->save();
	        if (userp(who)) who->save();
		return 1;
	}
	else if( obj->move(who) )
		{
			printf("���%sһ%s%s��\n", who->name(), obj->query("unit"), obj->name());
			message("vision", sprintf("%s����һ%s%s��\n", me->name(), obj->query("unit"), obj->name()), who );
			message("vision", sprintf("%s��%sһ%s%s��\n", me->name(), who->name(),
			obj->query("unit"), obj->name()), environment(me), ({me, who}) );
			me->save();
			if (userp(who)) who->save();
			return 1;
		}
		else return 0;
}
object i_have(object env,string name)
{
	int i;
	object *inv;
	object obj;
	if (objectp(obj = present(name,env))) return obj;
	inv=all_inventory(env);
	for(i=0;i<sizeof(inv);i++)
	{
		if (filter_color(inv[i]->query("name"))==name)
		return inv[i];
	}
	return 0;
}
string filter_color(string arg)
{
  if(!arg) return "";
  arg = replace_string(arg, BLK, "");
  arg = replace_string(arg, RED, "");
  arg = replace_string(arg, GRN, "");
  arg = replace_string(arg, YEL, "");
  arg = replace_string(arg, BLU, "");
  arg = replace_string(arg, MAG, "");
  arg = replace_string(arg, CYN, "");
  arg = replace_string(arg, WHT, "");
  arg = replace_string(arg, HIR, "");
  arg = replace_string(arg, HIG, "");
  arg = replace_string(arg, HIY, "");
  arg = replace_string(arg, HIB, "");
  arg = replace_string(arg, HIM, "");
  arg = replace_string(arg, HIC, "");
  arg = replace_string(arg, HIW, "");
  arg = replace_string(arg, NOR, "");
/*  arg = replace_string(arg, BBLK, "");
  arg = replace_string(arg, BRED, "");
  arg = replace_string(arg, BGRN, "");
  arg = replace_string(arg, BYEL, "");
  arg = replace_string(arg, BBLU, "");
  arg = replace_string(arg, BMAG, "");
  arg = replace_string(arg, BCYN, "");
  arg = replace_string(arg, HBRED, "");
  arg = replace_string(arg, HBGRN, "");
  arg = replace_string(arg, HBYEL, "");
  arg = replace_string(arg, HBBLU, "");
  arg = replace_string(arg, HBMAG, "");
  arg = replace_string(arg, HBCYN, "");
  arg = replace_string(arg, HBWHT, "");
  arg = replace_string(arg, NOR, "");
*/
  return arg;
}
int help(object me)
{
write(@HELP

ָ���ʽ : give <��Ʒ����> to <ĳ��>
      �� : give <ĳ��> <��Ʒ����>
 
    ���ָ��������㽫ĳ����Ʒ�����ˣ���Ȼ��������Ҫӵ��������Ʒ��
 
HELP
    );
    return 1;
}
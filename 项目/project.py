
import pandas as pd
import matplotlib.pyplot as plt

failCount=0
winCount=0
cou=0
count1=0
#养小动物
pet=[]
newcount=0
import random,time
class Animal:
    Health_Limit=100
    Crease_weight=5
    def __init__(self,name,type,weight,health,age=0,fullness=100,affinity=10):
        self.name=name
        self.type=type
        self.age=age
        self.health=health
        self.__weight=weight
        self.affinity=affinity
        self.skill=skill
        self.fullness=fullness
        self.skill=[]
    def status(self):
        print(f"他目前的体重是{self.__weight},年龄是{self.age},饱腹度为{self.fullness},"
              f"亲和度为{self.affinity},技能{self.skill}")
        if self.health<=60:
            print("健康值是"+f"{self.health}"+"你的宠物健康值较低，请为它提供疗伤，或者喂食")
        else:
            print(f"健康值是{self.health}")

    @property
    def weight(self):
        self.__weight+=Animal.Crease_weight
        return self.__weight

    @classmethod
    def limit(cls,self):
        if self.health<cls.Health_Limit:
            return True
        else:
            self.health=cls.Health_Limit
            return True



class Bag:
    def __init__(self):
        self.items=[]
        self.count=[]
        self.zio = zip(self.items, self.count)
    def add_item(self,new_item):
        if new_item in self.items:
            index=self.items.index(new_item)
            self.count[index]+=1
        else:
            self.items.append(new_item)
            self.count.append(1)
    def remove(self,item):
        index = item.index(item)
        if self.count[index]==0:
            self.items.remove(item)
            return 0
        else:
            self.count[index]-=1
    def show(self):
        print("背包目前物品以及数量：")
        for item,count in zip(self.items,self.count):
            print(f"{item}:{count}个")




class  Person:
    epithet=[]
    def __init__(self,name,sex,fortune,draft=0,money=2000,skill="无"):
         self.name=name
         self.sex=sex
         self.draft=draft
         self.money=money
         self.skill=skill
         self.fortune=fortune
    def information(self):
        print("玩家："+self.name+"\n"+"性别："+self.sex+"\n"+"经验值:",self.draft,"\n"+"金币数:",self.money,"\n"+"技能:"+self.skill)
        print(f"称号：{Person.epithet}")




class Cat(Animal):
    def __init__(self, name, type, weight, health,fullness=100, age=0, affinity=10, character="无", skill="无"):

        self.last_check_time=time.time()
        self.power=10
        super().__init__(name, type, weight, health)


    def _update_fullness(self,day):

            self.age += day / 1
            self.fullness -= day * 15
            self.fullness = max(0, self.fullness)  # 确保饱腹度不小于0

    def eat(self,food):
        if food=="小鱼":
            print("小猫很开心,蹭了蹭你的腿")
            self.fullness += 60
            if self.fullness >= 100:
                self.fullness = 100
        else:
            print("小猫很开心")
            self.fullness += 30


    def play_with_pet(self):
            print("你和宠物尽情嬉戏，它开心得直打滚~")
            # 玩耍消耗10饱腹度
            self.fullness = max(0, self.fullness - 10)

    def sleep(self):
        print(f"{self.name} 找了个舒适的地方开始睡觉。")
        self.health += 10  # 假设睡觉可恢复一定生命值
        if self.health > 100:
            self.health = 100

    def cure_pet(self,item,medicine1,medicine2,medicine3):
        print("你的宠物得到了治疗，状态好多了")
        if item==medicine1:

            self.health+=medicine1.function
        elif item==medicine2:
            self.health += medicine2.function
        else:
            self.health += medicine3.function
        print("健康度增加，可以查看属性哦")

    def attack(self,goal):
        damage=self.power
        goal.health-=damage
        print(f"{self.name}对{goal.name}进行了普通攻击，造成了{damage}点伤害")
    """def user_skill(self,skill,goal,skills):
        for i in skills:
            if i.name==skill and skill in self.skill:
                t=i

        if t.cast():
              print(f"{self.name}对{goal.name}使用了{t},"
                      f"对{goal.name}造成了{t.attack_power}点伤害")
        else:
                print(f"{self.name}使用技能失败!")


        else:
           print("没有可用的技能")
           self.attack(goal)
           return"""

    def user_skill(self, skill, goal, skills):

        found_skill = None
        for i in skills:
            if i.name == skill and skill in self.skill:
                found_skill = i
                break
        if found_skill:
            if found_skill.cast():
                print(f"{self.name}对{goal.name}使用了{found_skill.name}, "
                      f"对{goal.name}造成了{found_skill.attack_power}点伤害")
                goal.health-=found_skill.attack_power
            else:
                print(f"{self.name}使用技能失败!")
        else:
            print("没有可用的技能")
            self.attack(goal)
            return

    def mewo(self):
         print(f"{self.name}:喵喵~")
         time.sleep(2)
    def screch(self):
        print(f"{self.name}在磨爪子")
        time.sleep(2)

    def is_hungry(self):

        if self.fullness<60:
            print(f"{self.name} 饿了，需要找食物吃。")
            return True
        return False


    def is_healthy(self):

        if self.health < 30:
            print(f"{self.name} 状态不太好，需要休息或治疗。")
            return False
        return True
    def wash(self):
        print(f"{self.name}不愿意洗澡，并朝你喵了一声")
        choice=int(input("请选择你接下来的操作，1:强行洗澡，2：施展你的魅力"))
        if choice==1:
            print("亲和度减二")
            self.affinity-=2
            self.health+=2
        else:
            print("当然成功啦，亲和度加10")
            self.affinity+=10
            self.health+=2









class Dog(Cat):
     def __init__(self, name, type, weight, health,fullness=100, age=0, affinity=10, character="无", skill="无"):
         self.power=12
         super().__init__(name, type, weight, health)
     def mewo(self):
         print(f"{self.name}:汪汪！")
         time.sleep(2)
     def screch(self):
         print(f"{self.name}把小球叼给你")
         time.sleep(2)
     def eat(self,food):
         if food=="肉干":
             print("小狗很开心,朝你摇摇尾巴，饱食度加60")
             self.fullness+=60
             if self.fullness>=100:
                 self.fullness=100
         else:
             print("小狗很开心，饱食度加30")
             self.fullness+=30



     def wash(self):
        print(f"{self.name}不愿意洗澡，并朝你汪了一声")
        choice=int(input("请选择你接下来的操作，1:强行洗澡，2：施展你的魅力"))
        if choice==1:
            print("亲和度减二")
            self.affinity-=2
            self.health+=2
        else:
            print("当然成功啦,亲和度加一")
            self.affinity+=10
            self.health+=2




class Shopping:
    def __init__(self):
        self.item=[]
        self.itemvalues=[]
        self.result={}
    def display_all_items(self):
        if self.item:
            print("******普通商品信息*******:")

            for item in self.item[0:16]:
                print(item,end=" ")
            print("")
            for value in self.itemvalues[0:16]:
                print(value, end=" ")
            print("\n*******药品类*********")
            for item in self.item[16:19]:

                print(item,end=" ")
            print("")
            for value in self.item[16:19]:
                print(value)
            print("\n*******技能类（注意要在拥有宠物后才能购买，该技能仅限赋予宠物）*******")
            for item in self.item[19:]:
                print(item,end=" ")
            print("")
            for value in self.itemvalues[19:]:
                print(value, end=" ")
        else:
            print("商城内暂无商品")

    def purchase(self,choice5,person,shop,bag):
        while True:
            if choice5 in shop.result.keys():
                t=shop.item.index(choice5)
                person.money -=shop.itemvalues[t]
                if person.money>=0:

                    print("购买成功")
                    bag.add_item(choice5)
                    if len(pet)!=0:
                        if choice5 in self.item[18:]:

                            for item in pet:
                                item.skill.append(choice5)
                                print(item.skill)
                                return 1
                    return 1


                else:
                    print("金币不够")
                    person.money += shop.itemvalues[t]
                    return 0
            else:
                print("该商品不存在，请重新选择")
                return 0


class MedicineProduct:
    def __init__(self,name,price):
        self.name=name
        self.price=price
        self.function=0
    def Bfunction(self,function):
        self.function+=10
class Skill:
    def __init__(self,name,attack_power,probalility):
         self.name=name
         self.attack_power=attack_power
         self.probalility=probalility
    def cast(self):
        if random.random()<self.probalility:
            return True
        else:
           return  False

    def tain(self,power_increase,proper_increase):
        self.attack_power+=power_increase
        self.probalility+=proper_increase


class Monster:
    def __init__(self,name,health,power):
       self.name=name
       self.health=health
       self.power=power
    def attack(self,goal):
        damage=self.power
        goal.health-=self.power
        print(f"{self.name}对{goal.name}进行了攻击，伤害点{damage}")




class Bear(Cat):

        def eat(self, food):
            if food == "蜂蜜":
                print(f"{self.name} 非常开心地吃着 {food},饱食度加60！")
                self.fullness+=60
            else:
                print(f"{self.name} 吃着 {food}，饱食度加30。")
                self.fullness+=30

        def wash(self):
            print(f"{self.name}不愿意洗澡，并给了你一拳")
            choice = int(input("请选择你接下来的操作，1:强行洗澡，2：施展你的魅力"))
            if choice == 1:
                print("亲和度减二")
                self.affinity -= 2
                self.health += 2
            else:
                print("当然成功啦，亲和度加10，健康值加2")
                self.affinity += 10
                self.health += 2
        def mewo(self):
            print("它不愿意叫，太吵啦")
            time.sleep(2)
        def screch(self):
            print("它趁你不注意偷走了你厨房里的蜂蜜——")
            time.sleep(2)
def choiceanimal(pet1,pet2,pet3):
   global pet
   print("请选择你的宠物")
   print("_"*20)
   print("1.",pet1.name,"种类",pet1.type,"生命值",pet1.health)
   print("2.", pet2.name, "种类", pet2.type, "生命值", pet2.health)
   print("3.", pet3.name, "种类", pet3.type, "生命值", pet3.health)
   print("-"*20)
   lst={1:pet1,2:pet2,3:pet3}
   choice2=int(input("输入选择1-3"))
   try:
      while choice2:
        for i in lst.keys():
           if choice2==i:
             print(f"你选了一只小",{lst[i].type},"在接下来的时间里和它一起度过吧")
             print("是否为它命名T or F")
             bool=input("")
             if bool=="T":
                name_new=input("请输入你想为它起的名字")
                lst[i].name=name_new
                print("现在他有了新名字",name_new)

                pet.append(lst[i])

                break
             else:
                 print("ok")

                 pet.append(lst[i])
                 break

        break

   except ValueError:
       print("输入错误，请输入有效值")



def  feed_pet(choice,person,shop,bag):

    petOption=pet[choice]
    tu=petOption.fullness
    print("目前饱食度为%d"%tu)
    bag.show()
    item=input("请问想要给小可爱喂一些什么")
    while True:

        if item in bag.items:
            print("ok")
            bag.remove(item)
            petOption.eat(item)
            person.draft+=1
            option3 = ("还要继续喂食吗")
            if option3 == "y":
                print("ok,请输入")
            else:
                break
        else:
            print("快点给它喂食吧")
            break

def play_with_pet(choice,person,shop,bag):
    petOption=pet[choice]
    tun=petOption.affinity
    while True:

        item = input("请问想要给小可爱玩一些什么")
        bag.show()
        if item in bag.items:
            print("ok")
            bag.remove(item)
            petOption.play_with_pet()
            tun += 10
            print("亲和度增加十点")
            global count1
            count1 += 1
            person.draft+=1
            option=input("是否继续玩耍，y or n")
            if option=="y":
                print("ok")
            else:
                break
        else:
            print("请选择正确的选项")
            break

def stutus_pet(choice):
    petOption = pet[choice]
    petOption.status()

def cure_pet(choice,person,bag,medicine1,medicine2,medicine3):
    petOption=pet[choice]
    tun = petOption.affinity
    while True:
        item = input("选择想要给小可爱治愈的物品")
        bag.show()
        if item in bag.items:
            bag.remove(item)

            petOption.cure_pet(item,medicine1,medicine2,medicine3)
            tun +=10
            print("亲和度增加十点")
            global cou
            cou+=1
            person.draft+=10
        else:
            break


def cure(bag,shop):
    for i in range(len(pet)):

        print(pet[i].name)
    while True:
        choice19=int(input("请选择你想为哪个小动物治疗,查看他们的状态"))
        tu=choice19
        if tu in len(pet):
            pet[tu].status()
            number=int(input("是否治疗1 or 0"))
            if number==1:
                item = input("选择想要给小可爱治愈的物品")
                bag.show()
                bag.remove(item)
                pet[tu].cure_pet(item)
                global cou
                cou += 1

            else:
                continue
        else:
            print("输入错误")


def bath(i):

    print("清理可以增加一定的健康值哦\n")
    pet[i].wash()
    print("健康值加二")
    pet[i].health+=2
def skill(i,skills):
    print("经常练习可以增加技能成功率哦\n选择你想要提升的小动物")
    animalchoice = int(input(f"{pet[i].name}"))
    if pet[animalchoice].skill=="无":
         print("经过训练后")
         print("攻击力加一")
         pet[animalchoice].power += 1
    else:
        print("经过训练后")
        print("攻击力加一")
        print("技能加攻击力加一")
        print("技能成功率加一")
        choiceNew=random.choice(pet[animalchoice].skill)
        for item in skills:
            if choiceNew==item:

                item.attack_power+=1
                item.probalility+=1
                pet[animalchoice].power+=1
def sleepNow(i):
    pet[i].sleep()
def exit_program():
        print("感谢你的陪伴，期待下次再见！")
        return
def daliy(i):
    pet[i].screch()
def say(i):
    pet[i].mewo()
def petmenu(i,person,shop,bag,medicine1,medicine2,medicine3,skills):
    print("########欢迎进入陪伴宠物界面#######")
    while True:
        print("请选你要进的操作1,2..")
        print("1.喂食小动物")
        print("2.与宠物玩耍")
        print("3.为宠物疗伤")
        print("4.查看宠物状态")
        print("5.退出")
        print("6.为ta洗澡")
        print("7.技能训练")
        print("8.查看它现在在干什么")
        print("9.听一听它要说些什么")
        print("10.睡觉啦")
        choice8=input("请输入要进行的操作")
        action_mapping={
            "1":feed_pet,
            "2":play_with_pet,
            "3":cure_pet,
            "4":stutus_pet,
            "5":exit_program,
            "6":bath,
            "7":skill,
            "8":daliy,
            "9":say,
            "10":sleepNow
        }
        if choice8=="1":
            feed_pet( i,person,shop,bag)
        elif choice8=="2":
            play_with_pet( i,person,shop,bag)


        elif choice8=="3":
            cure_pet( i,person,bag,medicine1,medicine2,medicine3)
        elif choice8=="4":
            stutus_pet( i)
        elif choice8=="5":
            exit_program()
            break
        elif choice8=="6":
            bath(i)
        elif choice8=="7":
            skill(i,skills)
        elif choice8=="8":
             daliy(i)
        elif choice8 == "9":
             say(i)
        elif choice8=="10":
             sleepNow(i)
        else:
            exit_program()


def petCompanylist(person,bag,shop,medicine1,medicine2,medicine3,skills):
    print("你的小可爱已经等不及啦!!!")
    print("请选择————————")
    while True:
        for i,item in enumerate (pet):
            print("想要看看"+f"{item.name}吗",end=" ")
            choice7=input("Y OR N")
            if choice7=="Y":
                petmenu(i,person,bag,shop,medicine1,medicine2,medicine3,skills)

            else:
                print("ok")

        break


def battle(animal,monster,person,shop,skills,bag):
    print("**********欢迎进入模拟战场，进行匹配中，你要对战的是***********")
    bigmonster=random.choice(monster)
    health=bigmonster.health
    health1=animal.health
    print(f"{bigmonster.name}")
    while animal.health > 0 and bigmonster.health > 0:
            global failCount
            global winCount
            choice23=input("是否要施展技能 Y or N")
            if choice23=="Y":
                if animal.skill!=[]:
                    df=input("施展什么技能")
                    ty=animal.user_skill(df,bigmonster,skills)
            animal.attack(bigmonster)

            print(bigmonster.health)
            if bigmonster.health <= 0:
                print(f"{bigmonster.name} 已被击败！")
                thing = random.choice(shop.item)
                print(f"您获得{thing}")
                person.money+=100
                bag.add_item(thing)

                winCount+=1
                animal.health=health1
                bigmonster.health=health
                break
            bigmonster.attack(animal)
            if animal.health <= 0:
                print(f"{animal.name} 已被击败！")

                failCount+=1
                animal.health = health1
                bigmonster.health = health
                break
            if bigmonster.health<30:
                print("攻击力暴增")
                animal.health-=1.5*bigmonster.power
                if animal.health<=0:
                    print(f"{animal.name} 已被击败！")

                    failCount+=1
                    animal.health = health1
                    bigmonster.health = health
                    break
                elif bigmonster.health<=0:
                    print(f"{bigmonster.name} 已被击败！")
                    thing = random.choice(shop.item)
                    print(f"您获得{thing}")
                    person.money += 100
                    bag.add_item(thing)


                    winCount += 1
                    animal.health = health1
                    bigmonster.health = health
                    break
                else:
                    continue
    return


def personAttributeMenu():


        name_put = None
        sex_put = None
        fortune_put = None

        while True:
            print("\n1.姓名", "2.性别", "3.运气", "0.退出")
            choice = input("请输入你的选择（数字）: ")

            if choice == "0":
                print("返回")
                break

            if not choice.isdigit() or not (1 <= int(choice) <= 3):
                print("输入错误，请输入1-3的数字或0退出")
                continue

            if choice == "1":
                name_put = input("请输入你的姓名: ")
            elif choice == "2":
                sex_put = input("请输入你的性别: ")
            elif choice == "3":
                print("开启运气点数随机选取...")
                fortune_put = random.randrange(1, 11)  # 包含1-10
                print(f"恭喜你获得 {fortune_put} 点运气值!")

        # 检查所有属性是否已填写
        if all([name_put, sex_put, fortune_put]):
            person = Person(name_put, sex_put, fortune_put)
            return person
        else:
            print("错误：信息不完整（需填写姓名、性别并生成运气值）")
            return None



def main():
    pet1 = Cat("咪咪", "猫", 50, 80)
    pet2 = Dog("汪汪", "狗", 60, 80)
    pet3 = Bear("小熊", "熊", 100, 90)
    bag = Bag()
    shop = Shopping()
    monster1 = Monster("可爱小小怪", 100, 15)
    monster2 = Monster("可爱暴鼠", 150, 20)
    monster3 = Monster("可爱蝙魔", 200, 25)
    monster4 = Monster("可爱无敌怪", 300, 30)
    monster = [monster1, monster2, monster3, monster4]

    skill1 = Skill("水漫金山", 20, 70)
    skill2 = Skill("地狱烈焰", 23, 60)
    skill3 = Skill("金刚", 30, 69)
    skill4 = Skill("怒火", 38, 59)
    skill5 = Skill("致命", 50, 40)
    skill6 = Skill("裂爪突袭", 42, 80)
    skill7 = Skill("碎岩猛击", 35, 67)
    skills = [skill1, skill2, skill3, skill4, skill5, skill6, skill7]

    animal = Animal("无", "无", 0, 0)
    medicine1 = MedicineProduct("活力碎片", 70)
    medicine2 = MedicineProduct("伤药", 60)
    medicine3 = MedicineProduct("解毒药", 50)
    medicine1.Bfunction(30)
    medicine2.Bfunction(20)
    medicine3.Bfunction(10)
    shop.item = ["猫粮", "小鱼","狗粮", "胡萝卜", "香蕉", "苹果", "肉干", "蜂蜜", "温暖的窝", "毛球", "磨牙棒", "猫抓板",
                 "干草", "毛绒玩具", "超大爬架", "衣服", "活力碎片", "伤药", "解毒药", "水漫金山", "地狱烈焰",
                 "高级重生", "金刚", "怒火", "致命", "裂爪突袭", "碎岩猛击"]
    shop.itemvalues=[10,12,9,6,5,14,10,12,9,16,20,23,24,30,21,70,80,100,120,200,300,350,400,240,300]
    shop.result =dict(zip(shop.item,shop.itemvalues))
    print("欢迎来到动物派对")
    print("*"*20)

    option="1"

    print("请选择建立你的人物")
    person=personAttributeMenu()
    while option == "1":
        print("今天是第一天，请选择你需要进行的活动，1:查看属性,2:查看背包,3:进入商城,4:选择你心怡的宠物")
        choice2=input("")
        action_map={1:"查看属性",2:"查看背包",3:"进入商城",4:"选择你心怡的宠物"}
        action=action_map.get(int(choice2),lambda:print("输入错误"))
        if action=="查看属性":
            person.information()
        elif action=="查看背包":
            bag.show()
        elif action=="进入商城":
            print("***********欢迎进入Animal party商城************")
            shop.display_all_items()
            choice4=input(("购买物品吗 y or n"))
            while choice4:
                if choice4.lower()=="y":
                     choice5=input("输入你想要购买的商品")
                     if shop.purchase(choice5,person,shop,bag):
                         print("购买成功")
                     else:
                         print("购买失败")
                else:
                     break
                choice4 = input(("购买物品吗 y or n"))
        elif action=="选择你心怡的宠物":
            choiceanimal(pet1,pet2,pet3)
        option=input("请问是否继续选择，1:选择，0:拒绝")
        if option=="0":
            break
    choice6=input("第一天结束了，请问是否继续游戏，True or False")
    randomevents=["玩耍"]
    while  choice6:
        for day in range(2,10):
             print(f"_____第{day}天_____")
             print("欢迎进入Animal Party游戏")
             for item in pet:
                  item._update_fullness(day)
                  print(item.age)
             if randomevents==None:
                pass
             else:
                 try:
                    while True:
                        input_str = input(f"目前更新点任务{randomevents},需要进入随机事件吗y or n,并以y 0（选项）格式输入,不进入特殊事件选择n 0..")
                        parts = input_str.split()  # 假设用空格分隔输入内容
                        if len(parts) == 2:
                            choice14, choice15 = parts


                            if choice14.lower()=="y":
                                events=randomevents[int(choice15)]
                                if events=="抽奖功能":
                                    option8=random.choice(shop.item)
                                    print(f"恭喜你抽中{option8}")
                                    bag.add_item(option8)
                                    del randomevents[int(choice15)]
                                elif events=="生病":
                                    cure(bag,shop)
                                    del randomevents[int(choice15)]
                                elif events=="治疗之星":
                                    Person.epithet.append("治疗之星")
                                    del randomevents[int(choice15)]
                                elif events=="它是你的家人":
                                    Person.epithet.append("它是你的家人")
                                    del randomevents[int(choice15)]
                                elif events=="共同战友":
                                    Person.epithet.append("共同战友")
                                    del randomevents[int(choice15)]
                                elif events=="玩耍":
                                    choice40=int(choice15)
                                    play_with_pet( choice40,person,shop,bag)
                            else:
                                break
                        else:
                            print("输入格式错误，请重新输入")
                            continue
                 except  (ValueError, IndexError):
                     print("输入错误，请输入有效序号")



             for petirem in pet:
                if petirem.affinity>80:
                    print(f"恭喜你亲和度达到了80，触发了特殊事件,{petirem.name}开心的围着你转，获得了20点生命值")
                    petirem.health+=20
                    t=Animal.limit(petirem)

                if petirem.health<30:
                    print(f"请及时查看状态,陪伴你的小可爱")


             print("开始新的一天，请问你想要进行...，输入格式1,2")
             while True:
                menu = ["1.选择心怡的宠物", "2.进入商城", "3.查看属性", "4.查看背包", "5.陪伴你的小可爱", "6.冒险之旅","7:查看个人胜利情况","8:退出"]
                for times in range(len(menu)):
                    print(f"{menu[times]}")
                choice6=int(input("请输入你的选择"))
                if choice6==3:
                    person.information()
                elif choice6==4:
                    bag.show()
                elif choice6==5:
                    print(pet[0].name)
                    petCompanylist(person,shop,bag,medicine1, medicine2, medicine3,skills)
                elif  choice6==2:
                    print("***********欢迎进入Animal party商城************")
                    shop.display_all_items()
                    choice4=input(("购买物品吗 y or n"))
                    while choice4:
                      if choice4.lower()=="y":
                          choice5=input("输入你想要购买的商品")
                          if shop.purchase(choice5,person,shop,bag):
                             print("购买成功")
                          else:
                             print("购买失败")
                          choice4 = input(("购买物品吗 y or n"))
                      else:
                         break

                elif choice6==1:
                    if len(pet)<=2:
                       choiceanimal(pet1,pet2,pet3)

                    else:
                        print("目前支持最多两个宠物")

                elif choice6==6:
                    if len(pet)>0 and  all(smallanimal.age>5 for smallanimal in pet):

                       for i in range(len(pet)):
                           print(f"{i}:{pet[i].name}")
                       i = int(input("选择出战的宠物"))
                       battle(pet[i],monster,person,shop,skills,bag)
                       for animal in pet:
                           animal.affinity+=10

                    elif len(pet)==0:
                        print("你还没有宠物")
                    else:
                        print("您的宠物年龄还太小啦，不能进行战斗")

                elif choice6==7:
                    if winCount+failCount>=1:
                        plt.rcParams["font.sans-serif"] = "SimHei"

                        # 统计输赢次数

                        # 统计输赢次数
                        win_count = winCount
                        lose_count = failCount

                        # 创建DataFrame并写入表格
                        data = {'结果': ['赢', '输'], '次数': [win_count, lose_count]}
                        df = pd.DataFrame(data)
                        df.to_csv('competition_results.csv', index=False)

                        # 绘制饼图
                        labels = df['结果']
                        sizes = df['次数']
                        plt.pie(sizes, labels=labels, autopct='%1.1f%%', startangle=90)
                        plt.axis('equal')  # 保证饼图为正圆形
                        plt.title('与怪物比赛输赢情况')
                        plt.show()
                    else:
                        print("当前没有战斗，无法进入")
                        break
                elif choice6==8:
                    return

                option = input("请问是否继续选择，1:选择，0:拒绝")
                if option == "1":
                    continue
                else:
                    break

             choice6 = input(f"第{day}天结束了，请问是否继续游戏，True or False")
             if choice6 == "False":
                 return
             global newcount
             if newcount==0 and person.fortune>6:
                        randomevents.append("抽奖功能")

                        newcount=1

             if day>5:
                    randomevents.append("生病")

             if "治疗之星" not in Person.epithet and cou>3:
                    randomevents.append("治疗之星")
             if "它是你的家人" not in Person.epithet  and count1>3:
                    randomevents.append("它是你的家人")
             if "共同战友" not in Person.epithet  and winCount+failCount>1:
                    randomevents.append("共同战友")




def register():
    """用户注册功能"""
    while True:
        username = input("请输入用户名: ")
        password = input("请输入密码: ")
        confirm_password = input("请再次确认密码: ")

        if password == confirm_password:
            try:
                # 以追加模式打开文件，记录用户名和密码，每行格式为"用户名:密码"
                with open('user_info.txt', 'a') as file:
                    file.write(f"{username}:{password}\n")
                print("注册成功！")
                return
            except Exception as e:
                print(f"注册时出现错误: {e}")
        else:
            print("两次输入的密码不一致，请重新输入。")


def login():
    """用户登录功能"""
    username = input("请输入用户名: ")
    password = input("请输入密码: ")
    try:
        with open('user_info.txt', 'r') as file:
            for line in file.readlines():
                stored_username, stored_password = line.strip().split(':')
                if username == stored_username and password == stored_password:
                    print("登录成功！")
                    return True
            print("用户名或密码错误，请重新输入。")
            return False
    except FileNotFoundError:
        print("未找到用户信息文件，可能是尚未注册。")
        return False


if __name__ == "__main__":

    while True:
        print("1. 注册")
        print("2. 登录")
        print("3. 退出")
        choice = input("请选择操作: ")
        if choice == "1":
            register()
        elif choice == "2":
            bool=login()
            if bool==True:
                print("*********欢迎进入宠物派对********\n开始游戏.....")
                time.sleep(4)
                main()
            else:
                continue
        elif choice == "3":
            print("已退出程序。")
            break
        else:
            print("无效的选择，请重新输入。")

    print("本次游戏旅程到次结束啦~\n感谢你的参与，期待下次继续在宠物派对中欢乐冒险")
    print("一下是你的成就")
    print("最终对战情况：")

    print(f"我方{winCount}VS大大怪{failCount}")
    print("宠物最终结算")
    for i in pet:
         i.status()
    print(f"获得称号{Person.epithet}")
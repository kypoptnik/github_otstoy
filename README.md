github_otstoy
=============

true

Тема проекта: 
Аркадный продукт автосимулятора 90-х годов.
Идея: 
Управляя машинкой избегать столкновений и продвигаться по уровням до уровня профессионального гонщика!
Основные возможности:
1- управление машинкой, которая генерируется слева у экрана, избегая столкновения с потоком машин.
2- повышение уровня в зависимости от полученных очков, а так же с уровнем меняется и сложность.
3- сохранение/загрузка.
4- при столкновении очки снимаются, но не спускаются ниже 0.
5- управление ведется с помощью стрелочек на клавиатуре.
Детали:
Размер окна игры 1220х600. При столкновении машинки взрываются, как между собой так и с игроком, после столкновения 
с машинкой Игрока, машинка противника взрывается, а машинка Игрока респаунится в начальных координатах : 150, 268.
Машинки противников движутся справа налево, координаты выбираются рандомно в определенном промежутке 
"hge->Random_Int(1200,1690), hge->Random_Int(60,530)".
Так же рандомно выбирается цвет противника "g_tEColors[hge->Random_Int(0,4)]".
Счет, уровень в левом верхнем углу экрана, клавиши сохранения и загрузки обозначены в правом верхнем углу экрана 
через кливиши F5 F6.
В зависимости от уровня меняется скорость противника, согласно выражения "nitr=nitr+0.04;".
Полиморфизм используется в наслудуемом абстрактном классе, который использует виртульные методы.

Watch gameplay video here:

[![collage5](https://user-images.githubusercontent.com/38033580/38811579-9029232e-4192-11e8-80a4-35a1d4ec9fbf.jpg)
](http://www.youtube.com/embed/01cZ_v6islo)

                                          Description
 
Tools:
	
	● IDE: VS2015

	● Language: C++

	● Game engine: Irrlicht3D

Game Flow: 

![gameflow](https://user-images.githubusercontent.com/38033580/45288676-e9f4fe80-b4f3-11e8-9caa-f1dcec0a4f8a.PNG)

Gameplay Completion:

	Displaying basic elements:                  background, menu, skybox, map, player, enemy, coins, boxes

	Displaying additional information:     	    coin counter, life counter

	Player					    blue ninja

	Enemy					    red ninja

	In-game menu support (IGM)        	    ● Resume
		   			            ● Main Menu
					            ● Exit

Game Controls:

	move:	          left/right/up/down buttons 
	move directions:  left/right/up/down
	in-game menu:     ESC
	pause:	          SPACE


Audio:

	Music support

	Support for sound effects according to the events of the game

	Multiple channels


PathFinding algorithm

	u32 	     destinationCell        - текущий тайл врага

	vector3df    destinationPosition    - текущая позиция врага

	CH_DIRECTION direction = CH_D_NONE  - напрвление(для дальнейшего сохранения в него) лучшего следующего направления для движения врага

	vector3df    targetPosition	    - computes position of our target

	f32 minimalDistance = destinationPosition.getDistanceFromSQ(targetPosition); Возвращает квадрат расстояния от другой точки
									     computes initial value of metric for finding best position



// если корень мин дистанции > minimal distance between cells' centers.

// minimalDistance = Obtains maximal distance between cell's centers (squared).

if (sqrtf(minimalDistance) > _map->getMinimalDistance())

	minimalDistance = _map->getMaximalDistanceSquared();

	
// checks: is better position exists, if exists then uses it

array<CH_DIRECTION> directions = getAvailableDirections();

	        // в цикле выбираем наилучшее направление из массива в котром остались новые направления
		// путем получения расстояния между соседом и целью для каждого полученного напрвления
		// а потом сравниванием эту дистанцию с minimalDistance: если текущая дистанция меньше то инициализируем ее minimalDistance и в direction сохр это направление
		// повторем это в цикле и вычисляем наилучшее направление
		for (u32 i = 0; i < directions.size(); ++i) {

			// получаем следующий тайл согласно текущему напарвлению из массива
			u32 destinationCell = _map->getDestinationCell(_moving->getPosition(), directions[i]);
			// получаем его позицию
			vector3df destinationPosition = _map->getPosition(destinationCell);

			// вычисляем дистанцию от этого тайла до плеера
			f32 distance = destinationPosition.getDistanceFromSQ(targetPosition);

			if (distance < minimalDistance) {
				direction = directions[i];
				minimalDistance = distance;
			}

		}

		// adds current position to the list of used
		// to prevent up-down or left-right jittering when target 
		// is behind the obstacle
		_usedPositions.push_back(_moving->getPosition());

		// moves controlled entity
		_moving->move(direction);

***********************************************

array<CH_DIRECTION> EnemyMovingController::getAvailableDirections()
{
	u32 targetPosition = _target->getPosition();

	// если плеер нестоит на месте то
	if (_previousTargetPosition != targetPosition) {
		_usedPositions.clear();
		_previousTargetPosition = targetPosition;
	}

	// позиция врага
	u32 position = _moving->getPosition();

	// получить массив с возможными направлениями для 4-ех сторон
	// getAvailableDirections проверяет на припятствия четыре стороны от текущего тайла и возвр в массиве возможные стороны для передвижения врага
	array<CH_DIRECTION> directions = _map->getAvailableDirections(position);

	for (u32 i = 0; i < directions.size(); ++i)
	{
		// destination - следующая позиция для врага по полученному напрвлению из массива
		u32 destination = _map->getDestinationCell(position, directions[i]);
		// если destination уже есть в списке пройденных позиций то удаляем этот directions из имеющегося массива направлений
		if (_usedPositions.linear_search(destination) != -1) {
			directions.erase(i--, 1);
		}
	}

	return directions;
}




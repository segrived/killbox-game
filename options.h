namespace Options
{
    // Опции игрока
    namespace Player {
        // Количество жизней
        const int lifes = 5;
    }

	// Опции пули
	namespace Bullet {
		// Размер
		const float size = 0.01f;
		// Скорость
		const float speed = 0.025f;
		// Максимальное количество на одном экране
		const int maxPerScreen = 6;
	}
	
	
	// Опции машины
	namespace Machine {
		// Размер
		const float size = 0.2f;
		// Скорость передвижения
		const float speed = 0.02f;
	}
	
    
	// Опции фрага
	namespace Frag {
		// Размер
		const float size = 0.2f;
		// Стартовая скорость
		const float startSpeed = 0.01f;
		// Ускорение (на каждый отрисованый кадр)
		const float acceleration = 1.0002f;
		// Промежуток между генерацией врагов
		const float generatingSpeed = 2.0f;
		// Количество очков за попадание
        const int pointsPerHit = 100;
        
        // Обции босса
		namespace Boss {
			// Количество жизней
			const int lifes = 3;
			// Вероятность генерации босса (1 / значение)
			const int chance = 10;
			// Размер босса относительно обычного врага
			const float sizeMultipler = 1.4f;
            // Количество дополнительных очков за убийства босса
            const int pointsPerKill = 100;
		}
	}
}

// Размеры экрана для оконного и полноэкранного режимов
#define WINDOW_MODE_HEIGHT 400
#define WINDOW_MODE_WIDTH 400
#define FULLSCREEN_MODE_HEIGHT 800
#define FULLSCREEN_MODE_WIDTH 600

// Запускать по умолчанию в полноэкранном режиме
#define DEFAULT_FULLSCREEN false

// Показывать или не показывать количество доступных пуль
#define SHOW_AVAILABLE_BULLETS true
// Показывать или не показывать количество доступных жизней
#define SHOW_AVAILABLE_LIFES true
// !!! not implemented !!!
#define BONUS_SIZE 0.05f
#define BONUS_CHANCE 20
#define BONUS_SPEED_MIN 0.5f
#define BONUS_SPEED_MAX 1.0f

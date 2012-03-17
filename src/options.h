namespace Options
{
    // Опции игрока
    namespace Player {
        // Количество жизней
        const int lifes = 5;
    }

	// Опции пули
	namespace Bullet {
		const float size = 0.01f;   // Размер
		const float speed = 0.025f; // Скорость
		const int maxPerScreen = 6; // Максимальное количество на одном экране
	}
	
	// Опции машины
	namespace Machine {
		const float size = 0.2f;   // Размер
		const float speed = 0.02f; // Скорость
	}
	
	// Опции фрага
	namespace Frag {
		const float size = 0.2f;            // Размер
		const float startSpeed = 0.01f;     // Стартовая скорость
		const float acceleration = 1.0002f; // Ускорение (на каждый отрисованый кадр)
		const int generatingSpeed = 20;     // Промежуток между генерацией врагов (в долях секунды)
        const int pointsPerHit = 100;       // Количество очков за попадание
        // Опции босса
		namespace Boss {
			const int lifes = 3;              // Количество жизней
			const int chance = 10;            // Вероятность генерации босса (1 / значение)
			const float sizeMultipler = 1.4f; // Размер босса относительно обычного врага
            const int pointsPerKill = 100;    // Количество дополнительных очков за убийства босса
		}
	}
    
    // Опции бонуса
    namespace Bonus {
        const float size = 0.05f;    // Размер
        const int chance = 150;      // Шанс выпадения (1/значение в долю секунды)
        const float minSpeed = 0.5f; // Минимальная скорость
        const float maxSpeed = 1.0f; // Максимальная скорость
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
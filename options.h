// Размеры экрана для оконного и полноэкранного режимов
#define WINDOW_MODE_HEIGHT 400
#define WINDOW_MODE_WIDTH 400
#define FULLSCREEN_MODE_HEIGHT 800
#define FULLSCREEN_MODE_WIDTH 600

// Запускать по умолчанию в полноэкранном режиме
#define DEFAULT_FULLSCREEN false

// Размер фрага
#define FRAG_SIZE 0.2f
// Стартовая скорость фрагов
#define FRAG_STARTING_SPEED 0.01f
// Ускорение врагов
#define FRAG_ACCELERATION 1.0002f
// Промежуток между генерацией фрагов
#define FRAG_GEN_PAUSE 2.0f
// Количество жизней у босса
#define FRAG_BOSS_LIFES 3
// Вероятность генерации босса (1 / значение)
#define FRAG_BOSS_CHANCE 10
// Размер босса относительно обычных фрагов
#define FRAG_BOSS_SIZE_MULTIPLER 1.4f       
// Количество очков, дающихся дополнительно за убийства босса
#define FRAG_POINTS_PER_BOSS 1000
// Скорость путь
#define BULLET_SPEED 0.025f
// Размер пули
#define BULLET_SIZE 0.015f
// Размер машины
#define MACHINE_SIZE 0.2f
// Скорость перемещения машины
#define MACHINE_SPEED 0.02f
// Максимальное количество пуль на одном экане
#define MAX_BULLETS_PER_SCREEN 6
// Количество жизней у игрока
#define GAME_LIFES 5
// Количество очков за попадание
#define POINTS_PER_HIT 100
// Показывать или не показывать количество доступных пуль
#define SHOW_AVAILABLE_BULLETS true
// Показывать или не показывать количество доступных жизней
#define SHOW_AVAILABLE_LIFES true
// !!! not implemented !!!
#define BONUS_SIZE 0.05f
#define BONUS_CHANCE 20
#define BONUS_SPEED_MIN 0.5f
#define BONUS_SPEED_MAX 1.0f

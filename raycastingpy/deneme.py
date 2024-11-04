import pygame
import math

WIN_WIDTH, WIN_HEIGHT = 800, 600
# 800'e 600'lük bir pencere oluşturacağımız için bu değerleri tanımladık.

player_x, player_y = WIN_WIDTH // 2, WIN_HEIGHT // 2
# Oyuncunun başlangıç konumunu belirledik. Pencerenin ortasına gelecek şekilde ayarladık.

player_angle = 0
# Oyuncunun başlangıç açısını belirledik. 0 derece.


# Raycasting parametreleri
FOV = math.pi / 3
# 60 derece FOV belirledik. bu şunu ifade ediyor;
# Oyuncu 60 derecelik bir açı ile etrafına bakabiliyor.

NUM_RAYS = 240
# 120 tane ışın oluşturacağız. Bu ışınlar sayesinde 3D görüntü elde edeceğiz.

MAX_DEPTH = 800
# Maksimum derinlik belirledik. Bu değerin üzerindeki herhangi bir mesafe
# 800 piksel olarak kabul edilecek.

DELTA_ANGLE = FOV / NUM_RAYS
# Her bir ışın arasındaki açı farkını belirledik.
# bu 2 ışın arasındaki açı farkı 0.0052 radian olacak.

DISTANCE_PROJ_PLANE = (WIN_WIDTH // 2) / math.tan(FOV / 2)
# Projeksiyon düzlemine olan uzaklığı belirledik.
# burdaki matematiksel işlem şu şekilde;
# Projeksiyon düzlemine olan uzaklık = (Pencere genişliği / 2) / tan(FOV / 2)
# bu işlem sonucunda projeksiyon düzlemine olan uzaklık 400 olacak.
# projeksiyon düzlemi, oyuncunun ekranı gördüğü düzlemi ifade eder.

# Duvar rengi
WALL_COLOR = (0, 255, 0)
# Duvar rengini belirledik. Yeşil renk.

# Pygame başlatma
pygame.init()
# Pygame'i başlattık.

screen = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGHT))
# Pencere oluşturduk. 800'e 600'lük bir pencere oluşturduk.

clock = pygame.time.Clock()
# Oyun döngüsünü kontrol etmek için bir saat oluşturduk.

# Basit bir duvar haritası (1 = duvar, 0 = boş alan)
world_map = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]
# 7x10'luk bir harita oluşturduk. 1'ler duvarları, 0'lar boş alanları temsil ediyor.

TILE_SIZE = 80
# Her bir karenin boyutunu belirledik. 80x80 piksel.

# Haritada belirli bir koordinatın duvar olup olmadığını kontrol eden fonksiyon
def is_wall(x, y):
    # x ve y koordinatlarını harita koordinatlarına çeviriyoruz.
    map_x, map_y = int(x / TILE_SIZE), int(y / TILE_SIZE)
    # Eğer koordinatlar harita sınırlarının içindeyse ve o koordinatta duvar varsa True döndürüyoruz.
    if 0 <= map_x < len(world_map[0]) and 0 <= map_y < len(world_map):
        return world_map[map_y][map_x] == 1
    return False
	# Eğer koordinatlar harita sınırlarının dışındaysa veya o koordinatta duvar yoksa False döndürüyoruz.

def raycasting(screen):
    # RAY sayısı kadar döngü oluşturuyoruz. RAY sayısı, bizim ışın sayımız.
	for ray in range(NUM_RAYS):
		# Işın açısını hesapla
		ray_angle = player_angle - FOV / 2 + ray * DELTA_ANGLE
		# burdaki mateamatiksel işlem şu şekilde;
		# Işın açısı = Oyuncu açısı - FOV / 2 + ışın * ışın açı farkı
		# bu işlem sonucunda ışın açısı -0.523599 olacak.
		# ışın açısı, ışının yönünü belirler.
		# yani ışın, -0.523599 radian açı ile başlayacak.
		for depth in range(MAX_DEPTH):
			# Işının hedef konumunu hesapla
			target_x = player_x + depth * math.cos(ray_angle)
			# Işının x koordinatını hesapla
			target_y = player_y + depth * math.sin(ray_angle)
			# Işının y koordinatını hesapla

			# Duvara çarptığında işlemi sonlandır
			if is_wall(target_x, target_y):
				# Duvarın derinliğini hesapla
				# depth *= math.cos(player_angle - ray_angle)  # Balık gözü efektini düzelt
				# burda ki matematiksel işlem şu şekilde;
				# Derinlik = Derinlik * cos(Oyuncu açısı - Işın açısı)
				# bu işlem sonucunda derinlik 800 olacak.
				# bu işlem, balık gözü efektini düzeltmek için yapılır.
				wall_height = TILE_SIZE * WIN_HEIGHT / (depth * math.cos(player_angle - ray_angle))
				# Duvarın yüksekliğini hesapla
				color_intensity = 1 - min(1, depth / MAX_DEPTH)  # Derinlikten dolayı rengi karart
				# Renk yoğunluğunu hesapla
				color = (WALL_COLOR[0] * color_intensity, WALL_COLOR[1] * color_intensity, WALL_COLOR[2] * color_intensity)
				# Duvar
				print(color)
				# Duvarı çizin
				pygame.draw.line(screen, color,
                 (ray * WIN_WIDTH / NUM_RAYS, WIN_HEIGHT // 2 - wall_height // 2),
                 (ray * WIN_WIDTH / NUM_RAYS, WIN_HEIGHT // 2 + wall_height // 2))
				pygame.draw.line(screen, (255, 0, 0), (player_x, player_y), (target_x, target_y), 1)
				pygame.draw.circle(screen, (255, 0, 0), (int(target_x), int(target_y)), 5)

				break

# Oyuncu hareketleri için fonksiyon
def movement():
    global player_x, player_y, player_angle
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        player_angle -= 0.05
    if keys[pygame.K_RIGHT]:
        player_angle += 0.05
    if keys[pygame.K_UP]:
        player_x += 5 * math.cos(player_angle)
        player_y += 5 * math.sin(player_angle)
    if keys[pygame.K_DOWN]:
        player_x -= 5 * math.cos(player_angle)
        player_y -= 5 * math.sin(player_angle)

# Ana döngü
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((0, 0, 0))  # Ekranı temizle
    movement()  # Oyuncu hareketini uygula
    raycasting(screen)  # Raycasting çizimini uygula
    pygame.display.flip()  # Ekranı güncelle
    clock.tick(30)  # FPS sınırlama

pygame.quit()

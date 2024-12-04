#version 330 core

// Выходной цвет в формате RGBA
out vec4 FragColor;

// Импорт текущей позиции из вершинного шейдера
in vec3 crntPos;
// Импорт нормали из вершинного шейдера
in vec3 Normal;
// Импорт цвета из вершинного шейдера
in vec3 color;
// Импорт текстурных координат из вершинного шейдера
in vec2 texCoord;
// Импорт позиции фрагмента относительно света
in vec4 fragPosLight;

// Получение текстурных юнитов из основной программы
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D shadowMap;
uniform samplerCube shadowCubeMap;
// Получение цвета света из основной программы
uniform vec4 lightColor;
// Получение позиции света из основной программы
uniform vec3 lightPos;
// Получение позиции камеры из основной программы
uniform vec3 camPos;
// Получение значения дальнего плана (farPlane)
uniform float farPlane;

// Функция расчета освещения от точечного источника света
vec4 pointLight()
{	
	// Вектор от фрагмента до источника света
	vec3 lightVec = lightPos - crntPos;

	// Интенсивность света с учетом расстояния
	float dist = length(lightVec);
	float a = 0.0003f;
	float b = 0.00002f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// Расчет фонового освещения (ambient)
	float ambient = 0.20f;

	// Расчет диффузного освещения (diffuse)
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Расчет зеркального освещения (specular)
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

	// Значение тени
	float shadow = 0.0f;
	vec3 fragToLight = crntPos - lightPos;
	float currentDepth = length(fragToLight);
	// Убираем "акне теней" за счет смещения (bias)
	float bias = max(0.5f * (1.0f - dot(normal, lightDirection)), 0.0005f); 

	// Радиус выборки для сглаживания теней
	int sampleRadius = 2;
	float offset = 0.02f;
	for(int z = -sampleRadius; z <= sampleRadius; z++)
	{
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowCubeMap, fragToLight + vec3(x, y, z) * offset).r;
				// Учитываем деление на farPlane
				// Также текущая глубина не находится в диапазоне [0, 1]
				closestDepth *= farPlane;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
	}
	// Усредняем значение тени
	shadow /= pow((sampleRadius * 2 + 1), 3);

	// Возвращаем итоговое освещение
	return (texture(diffuse0, texCoord) * (diffuse * (1.0f - shadow) * inten + ambient) + texture(specular0, texCoord).r * specular * (1.0f - shadow) * inten) * lightColor;
}

// Функция расчета освещения от направленного источника света
vec4 direcLight()
{
	// Расчет фонового освещения (ambient)
	float ambient = 0.20f;

	// Расчет диффузного освещения (diffuse)
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Расчет зеркального освещения (specular)
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

	// Значение тени
	float shadow = 0.0f;
	// Координаты света в пространстве теней
	vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
	if(lightCoords.z <= 1.0f)
	{
		// Переводим из диапазона [-1, 1] в [0, 1] для работы с картой теней
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		float currentDepth = lightCoords.z;
		// Убираем "акне теней" за счет смещения (bias)
		float bias = max(0.025f * (1.0f - dot(normal, lightDirection)), 0.0005f);

		// Сглаживание теней
		int sampleRadius = 2;
		vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
		// Усредняем значение тени
		shadow /= pow((sampleRadius * 2 + 1), 2);
	}

	// Возвращаем итоговое освещение
	return (texture(diffuse0, texCoord) * (diffuse * (1.0f - shadow) + ambient) + texture(specular0, texCoord).r * specular  * (1.0f - shadow)) * lightColor;
}

// Функция расчета освещения от прожектора
vec4 spotLight()
{
	// Контролирует размер освещаемой области
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// Расчет фонового освещения (ambient)
	float ambient = 0.20f;

	// Расчет диффузного освещения (diffuse)
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Расчет зеркального освещения (specular)
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

	// Расчет интенсивности света на основе угла к центру конуса
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Значение тени
	float shadow = 0.0f;
	vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
	if(lightCoords.z <= 1.0f)
	{
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		float currentDepth = lightCoords.z;
		float bias = max(0.00025f * (1.0f - dot(normal, lightDirection)), 0.000005f);

		int sampleRadius = 2;
		vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
		shadow /= pow((sampleRadius * 2 + 1), 2);
	}

	// Возвращаем итоговое освещение
	return (texture(diffuse0, texCoord) * (diffuse * (1.0f - shadow) * inten + ambient) + texture(specular0, texCoord).r * specular * (1.0f - shadow) * inten) * lightColor;
}

// Основная функция
void main()
{
	// Выводим финальный цвет
	FragColor = pointLight();
}

#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoord;

//texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	//TEXTURA FINAL QUE APLICAREMOS
	vec4 tx1 = texture(texture1, TextCoord);
	vec4 tx2 = texture(texture2, TextCoord);
	vec4 finalTextura = mix(tx1, tx2, .5);

	//ambient
	float ambientI = .3;
	vec3 ambient = ambientI * lightColor;
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 1.0;
	vec3 viewDir = normalize (viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
	vec3 specular = specularStrength * spec * lightColor;

	//resultado
	vec3 result = (ambient + diffuse + specular) ;
	FragColor = mix(vec4(result,1.0), finalTextura, .7);
	//FragColor = vec4(result, 1.0);
}
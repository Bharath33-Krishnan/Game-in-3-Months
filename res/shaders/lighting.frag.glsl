#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
//in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragTangent;
in mat3 TBN;
in mat3 transTBN;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture2;
uniform sampler2D heightMap;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS 20
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec3 attenuation;
    vec4 color;
};

// Input lighting values
uniform int max_lights;
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;
uniform float shininess;
uniform float gamma;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir, float height_scale)
{ 
    float height =  texture(heightMap, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
    return texCoords - p;    
} 


void main() 
{


    vec3 tanViewPos =  transTBN * viewPos;
    vec3 tanFragPos =  transTBN * fragPosition;

    vec3 tanviewDir = normalize(tanViewPos - tanFragPos);
    
    //Parallax Mapping Looks weird though
    // vec2 texCoords = ParallaxMapping(fragTexCoord,tanviewDir,.08);

    vec2 texCoords = fragTexCoord;
    float shine = shininess * 16.0 * texture(specularMap,texCoords).r;

    int blinn = 1;
    // Texel color fetching from texture sampler
    vec4 texelColor = vec4(pow(texture(texture0, texCoords).rgb, vec3(gamma)),1.0);


    vec3 lightDot = vec3(0.0);

    // obtain normal from normal map in range [0,1]
    vec3 normal = texture(texture2, texCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0); 
    normal = normalize(TBN * normal);

    // finalColor = vec4(normal,1.0);
    // return;


    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);


    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            float lightDistance = 0.0;
            float attenuation = 1.0;
            vec3 light = vec3(0.0);
            // vec3 tanLightPos = transTBN * lights[i].position;

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].target - lights[i].position);
                attenuation = 1.0/length(lights[i].attenuation);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                light = (lights[i].position - fragPosition);
                lightDistance = length(light);
                light = normalize(light);
                attenuation = 1.0 / (lights[i].attenuation.x + lights[i].attenuation.x * lightDistance + 
                    lights[i].attenuation.z* (lightDistance*lightDistance));
            }
            vec3 halfwayDir = normalize(light + viewD);

            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb*NdotL*attenuation;

            float specCo = 0.0;
            if (NdotL > 0.0 && blinn == 0) specCo = pow(max(0.0, dot(viewD, reflect(-(light), normal))),16); // 16 refers to shine
            if (NdotL > 0.0 && blinn == 1) specCo = pow(max(0.0, dot(halfwayDir, normal)),16); // 16 refers to shine
            specular += specCo * shine * attenuation;
        }
    }
    finalColor = (texelColor*((colDiffuse + vec4(specular, 1.0))*vec4(lightDot, 1.0)));
    finalColor += texelColor*(ambient/10.)*colDiffuse;

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));

}

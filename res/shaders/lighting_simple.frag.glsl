#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
//in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS              4
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

void main() 
{

    float gamma = 2.2;
    float shine = 16.0;
    int blinn = 1;
    // Texel color fetching from texture sampler
    vec4 texelColor = vec4(pow(texture(texture0, fragTexCoord).rgb, vec3(gamma)),1.0);

    vec3 lightDot = vec3(0.0);

    vec3 normal = normalize(fragNormal);
    // obtain normal from normal map in range [0,1]
    // vec3 normal = texture(normalMap, fragTexCoord).rgb;
    // // transform normal vector to range [-1,1]
    // normal = normalize(normal * 2.0 - 1.0); 



    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    // NOTE: Implement here your fragment shader code


        // if (lights[0].enabled == 1)
        // {
        //     vec3 light = vec3(0.0);

        //     if (lights[0].type == LIGHT_DIRECTIONAL)
        //     {
        //         light = -normalize(lights[i].target - lights[i].position);
        //     }

        //     if (lights[0].type == LIGHT_POINT)
        //     {
        //         light = normalize(lights[i].position - fragPosition);
        //     }

        //     float NdotL = max(dot(normal, light), 0.0);
        //     lightDot += lights[i].color.rgb*NdotL;

        // }


    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].target - lights[i].position);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                light = normalize(lights[i].position - fragPosition);
            }

            vec3 halfwayDir = normalize(light + viewD);
            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb*NdotL;

            float specCo = 0.0;
            if (NdotL > 0.0 && blinn == 0) specCo = pow(max(0.0, dot(viewD, reflect(-(light), normal))),shine); // 16 refers to shine
            if (NdotL > 0.0 && blinn == 1) specCo = pow(max(0.0, dot(halfwayDir, normal)),shine); // 16 refers to shine
            specular += specCo;
        }
    }

    finalColor = (texelColor*((colDiffuse + vec4(specular, 1.0))*vec4(lightDot, 1.0)));
    finalColor += texelColor*(ambient/10.0)*colDiffuse;

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));
}

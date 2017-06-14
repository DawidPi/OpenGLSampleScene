#version 400

#define M_PI 3.1415926535897932384626433832795

in vec2 fs_texCoords;
in vec4 normalPosition;
in vec4 worldPosition;
in float vertexDistanceFromLight;

uniform bool useLighting;
uniform bool isLightSource;
uniform vec4 cameraPosition;
uniform vec4 lookDirection;
uniform vec4 lightPosition;
uniform vec3 lightColor;
uniform bool useHalo;
uniform sampler2D fs_texture;
in vec4 fs_normal;

out vec4 fs_color;


void main(void)
{
    vec4 chosenColor;
    chosenColor = texture(fs_texture, fs_texCoords);


    float colorAmbientScale = 0.05;
    vec3 ambientColor = vec3(colorAmbientScale, colorAmbientScale, colorAmbientScale) * chosenColor.rgb;

    if(isLightSource){
        fs_color = 2.5*vec4(chosenColor.rgb, 1.0);
    } else {
        vec4 incidentRayDiffuseVector = vec4(lightPosition.xyz,0.0);
        float lightingFactor = dot(normalize(incidentRayDiffuseVector), normalize(normalPosition));
        lightingFactor = clamp(lightingFactor, 0.0, 1.0);

        vec4 incidentRayVector = normalize(lightPosition - worldPosition);
        vec3 eyeDirection = normalize(lookDirection.xyz);
        vec3 reflection = reflect(incidentRayVector.xyz, normalize(normalPosition.xyz));
        //float reflectFactor = dot(eyeDirection, reflection);
        float reflectFactor = cos(acos((dot(normalize(worldPosition - cameraPosition).xyz, normalize(normalPosition.xyz)))) - M_PI/2);
        reflectFactor = clamp(reflectFactor, 0.0, 1.0);//(0.0, reflectFactor);
        reflectFactor = reflectFactor;
        float bluething =  1 * pow(reflectFactor,20);

        float lightPower = 320000;
        vec3 commonColor = chosenColor.rgb * lightColor /pow(vertexDistanceFromLight, 2);
        vec3 diffuseColor = commonColor * lightingFactor * lightPower;
        vec3 specularColor = vec3(0);// commonColor * pow(reflectFactor,50) * 25*lightPower/(distance(cameraPosition, worldPosition));
        fs_color = vec4(ambientColor + diffuseColor + specularColor, chosenColor.a);
        if(useHalo)
            fs_color.b += bluething;
    }
}
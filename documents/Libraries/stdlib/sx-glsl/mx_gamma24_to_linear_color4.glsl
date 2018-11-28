void mx_gamma24_to_linear_color4(vec4 _in, out vec4 result)
{
    vec4 gamma = vec4(2.400000095367432, 2.400000095367432, 2.400000095367432, 1.);
    result = pow( max( vec4(0., 0., 0., 0.), _in ), gamma );
}

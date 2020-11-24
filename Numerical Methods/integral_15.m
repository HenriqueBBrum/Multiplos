function integral_15(f,a,b,m)
  
  printf("Resposta da Regra dos Trapézios repetidos %f\n",trapezios(f,a,b,m))
  printf("Resposta da Regra 1/3 de Simpson repetida %f\n",simpson(f,a,b,m))
  
endfunction



function retorno = trapezios(f,a,b,m)
  h = (b-a)/m;
  resposta = 0.5*(f(a)+f(b));
  for i = 1:m-1
    resposta+=f(a+i*h);
  endfor
  resposta*=h;
  retorno = resposta;
  
  
endfunction

function retorno = simpson(f,a,b,m)
  h = (b-a)/m;
  resposta = (f(a)+f(b));
  for i = 1:m-1
    if(rem(i,2)==1)
      resposta+=(4*f(a+i*h));
    else
      resposta+=(2*f(a+i*h));
    endif
  endfor
  resposta*=h*1/3;
  retorno = resposta;
  
endfunction


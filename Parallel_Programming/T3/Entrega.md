# Programação Paralela

### Aluno: Henrique Becker Brum
### Matrícula: 201810077

## Results:

	Test  A , SCHED = RUNTIME, chunk 0 : using mutex (expecting correct results)
	BCABCBCACBACBCABCACACACBCBCABCACACBCBABABCACABACBCBCBCBCACBA
	A=17 B=19 C=24

	Test B , SCHED = RUNTIME, chunk 0 : no mutex (expecting wrong results)
	BBCABACBCACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBA--
	A=19 B=20 C=19

	 ------------------------------------------------------------------------------------------------

	Test  A , SCHED = STATIC, chunk 0 : using mutex (expecting correct results)
	CACBACBABCBCABCABCBCBACBCBCACABCBACBACBCACBABCACACBABABABAAA
	A=20 B=20 C=20

	Test B , SCHED = STATIC, chunk 0 : no mutex (expecting wrong results)
	AABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC--
	A=20 B=19 C=19

	 ------------------------------------------------------------------------------------------------

	Test  A , SCHED = STATIC, chunk 15 : using mutex (expecting correct results)
	CBCABCACABABACABCBCBACACACBABACABABACACACBABCBABAAAAAAAAAAAA
	A=30 B=15 C=15

	Test B , SCHED = STATIC, chunk 15 : no mutex (expecting wrong results)
	CBACBACBACABCABABACBABCBACBACBACBACBACBA-CACACA-AAAAAAAAAAAA
	A=29 B=14 C=15

	 ------------------------------------------------------------------------------------------------

	Test  A , SCHED = DYNAMIC, chunk 0 : using mutex (expecting correct results)
	ABCBCABCABABCABACACBCABACBCBCACBCBCABACABCACBCBABABACABABACB
	A=20 B=21 C=19

	Test B , SCHED = DYNAMIC, chunk 0 : no mutex (expecting wrong results)
	BBABCBCABABCBABCABCABCBCABABACBACBACBCABCABCBACBACBCABCABC--
	A=17 B=23 C=18

	 ------------------------------------------------------------------------------------------------

	Test  A , SCHED = DYNAMIC, chunk 15 : using mutex (expecting correct results)
	CACBCACBCBACACACABACBCBCACBABCBABACBCBACABACACBCBCCCCCCCCCCC
	A=15 B=15 C=30

	Test B , SCHED = DYNAMIC, chunk 15 : no mutex (expecting wrong results)
	BCBACBACBABCABCBCACBACBCBACBACBCBACBACBAC-ACACCA-CCCCCCCCCCC
	A=14 B=15 C=29

	 ------------------------------------------------------------------------------------------------






Foram testados os schedules static, dynamic, guided com chunk não definido e com chunk de tamanho 15 usando mutex, Test A,  e sem mutex, Teste B além desses três tipos de schedules também foi testado o auto e o runtime.

De modo geral quanto maior o chunk em relação ao tamanho total do vetor mais desparelho fica a quantidade de cada letra. Já relacionada a cada schedule, houve leve modificação do resultado entre schedule, dynamic e guided quando chunk = 0, já quando o chunk = 15,  o  guided dividiu mais porporcionalmente o tempo.

Quanto aos modos runtime e auto, o tempo de cada thread foi divido de maneira similar as outros modos quando o tamanho de chunk foi 15. Em todos os modos de schedule quando não foi usado mutex o resultado saiu errado.

O resultado mostrado não é o completo para ver o completo abra results.txt

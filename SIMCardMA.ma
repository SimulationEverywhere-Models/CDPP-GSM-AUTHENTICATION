%CDPlusPlus_Builder_Version_1.0.0

[top]
components : SIMCard@SIMCard 
out : Id
out : SRES_2 
in : On
in : Rand 
Link : On On@SimCard
Link : Rand Rand@SimCard 
Link : Id@SimCard Id
Link : SRES_2@SIMCard SRES_2

[SIMCard]
preparation : 00:00:03:00
distribution : normal
mean : 50
deviation : 25

data <- scan("stdin",quiet=T,what="character")

data1 <- gsub(pattern="Total energy deposited: ",
	      replacement="",
	      x=data)


app=require("express")()
bodyparser=require("body-parser")
app.use(bodyparser.urlencode(extended))
app.set("view engine",'pug')
app.set('views',"/")
app.get("/",function(req,res){
    res.render("form")
})

app.post("/",function(res,req){
    res.send("u entered",req.body)
})
app.listen(3000,function(){
    console.log("server is running")
})
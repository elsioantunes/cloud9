


    function getCommand(){}
    function GameDisplay(){}

    function Regras(){
        return {
        }
    }

    function runGames(numGames, beQuiet){
        var regras = new Regras()
        var games = []
        for(var i in numGames){
            game = new regras.newGame()
            game.run()
            Games.push(game)
        }
    }
    
    var args = getCommand()
    var relatorio = runGames(args)
    
    
    
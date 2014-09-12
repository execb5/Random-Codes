// Environment code for project tarefa2.mas2j

import jason.asSyntax.*;
import jason.environment.*;
import java.util.logging.*;

public class MyCuteEnvironment extends Environment {

    private Logger logger = Logger.getLogger("tarefa2.mas2j."+MyCuteEnvironment.class.getName());

    /** Called before the MAS execution with the args informed in .mas2j */
    @Override
    public void init(String[] args) {
        super.init(args);
        addPercept(Literal.parseLiteral("percept(demo)"));
    }

    @Override
    public boolean executeAction(String agName, Structure action) {
		if(((Literal)action).getFunctor().equals("do")) {
			Term t = action.getTerm(0);
			logger.info("Doing task " + t);
			addPercept(Literal.parseLiteral("done(" + t + ")"));
		}
		else
			logger.info("executing: "+action+", but not implemented!");
        return true;
    }

    /** Called before the end of MAS execution */
    @Override
    public void stop() {
        super.stop();
    }
}


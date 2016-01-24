#include <Wt/WServer>

#include "Application.h"

int main(int argc, char **argv)
{
	try
	{
		Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

		server.addEntryPoint(Wt::Application, [](const Wt::WEnvironment& env)
		{
			return new Application(env);
		});

		server.run();
	} catch (Wt::WServer::Exception& e)
	{
		std::cerr << e.what() << std::endl;
	} catch (std::exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}


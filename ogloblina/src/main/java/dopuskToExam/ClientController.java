package dopuskToExam;

import java.util.List;

/**
 * Created by Alena on 17.06.2017.
 */
public interface ClientController {void saveNewClient(Clients newClient);
    List<Clients> getAllClients();
    void deleteClient(int client_id);
    Clients getByID(int client_id);
    void updateClient(Clients clientUpdate);

}

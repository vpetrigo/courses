fun sendMessageToClient(client: Client?, message: String?, mailer: Mailer) {
    client?.personalInfo?.email?.let { mailer.sendMessage(it, message ?: return) }
}

class Client (val personalInfo: PersonalInfo?)
class PersonalInfo (val email: String?)
interface Mailer {
    fun sendMessage(email: String, message: String)
}

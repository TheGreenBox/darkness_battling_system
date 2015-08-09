#include "output_format.h"

void AnswerFormattedPrint(
    const std::vector<TProblemSolution>& solutions,
    std::ostream& out
) {
    Json::Value jsonOut(Json::arrayValue);

    for (const auto& sol : solutions) {
        Json::Value jsonSol(Json::objectValue);
        jsonSol["problemId"] = Json::Value(
            static_cast<Json::Value::UInt64>(sol.ProblemId)
        );
        jsonSol["seed"] = Json::Value(
            static_cast<Json::Value::UInt64>(sol.Seed)
        );
        jsonSol["tag"] = Json::Value(sol.Tag);
        jsonSol["solution"] = Json::Value(sol.Solution);
        jsonOut.append(jsonSol);
    }

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";  // without any indentation
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(jsonOut, &out);
    out << std::endl;
}
